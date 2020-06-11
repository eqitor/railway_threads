#include "Passenger.h"
#include <condition_variable>
#include "RandomIntGenerator.h"


unsigned int Passenger::id_counter = 0;

Passenger::Passenger(Station* start_station){
    
    passenger_id = id_counter++;
    actual_station = start_station;
    is_active = true;
};

Passenger::Passenger(){};

Passenger::~Passenger(){};

void Passenger::exist(){

    while (is_active)
    {   


        
        
        //SynchOut::print("Passenger " + std::to_string(passenger_id) + " is visiting " + actual_station->get_station_name());
        int buy_success;
        do
        {   
            this->actual_station->add_visitor(this->passenger_id);
            std::this_thread::sleep_for(std::chrono::milliseconds(3000 + RandomIntGenerator::generate(-500,500)));\
            this->actual_station->remove_visitor(this->passenger_id);
            set_destination();
            buy_success = try_buy_ticket();
        } while ( !buy_success );
        

        
        this->actual_station->add_platform_id(this->passenger_id);
        //czekaj na pociąg
        //SynchOut::print("Passenger " + std::to_string(passenger_id) + " is waiting for train " + selected_train->get_name());
        std::unique_lock<std::mutex> lk(selected_train->train_mutex);
        selected_train->train_cv.wait(lk, [&]{return actual_station->get_station_id() == selected_train->next_station->get_station_id();});
        this->actual_station->remove_platform_id(this->passenger_id);
        //wsiądź jedź i wysiądź na stacji
        //SynchOut::print("Passenfer " + std::to_string(passenger_id) + " in on the way to " + destination_station->get_station_name());
        this->selected_train->get_in();
        //jedz
        selected_train->train_cv.wait(lk, [&]{return destination_station->get_station_id() == selected_train->next_station->get_station_id();});
        //wysiadam
        this->selected_train->get_out();
        this->actual_station->remove_visitor(this->passenger_id);
        this->selected_train->free_ticket();
        this->actual_station = this->destination_station;
        
        
    }

    SynchOut::print("Passenfer " + std::to_string(passenger_id) + " stops.");
    
};

void Passenger::set_destination(){

    unsigned int new_destination_id;
    do{
        static thread_local std::uniform_int_distribution<> wait(0, Station::get_stations_ammount()-1);
        new_destination_id = wait(range);

    } while (new_destination_id == actual_station->get_station_id());
    
    destination_station = Map::find_station(new_destination_id);

};

bool Passenger::try_buy_ticket(){
    
    std::vector<TicketBooth*> booths = this->actual_station->get_booths_vector();
    

    int selected_booth_index = RandomIntGenerator::generate(0, actual_station->get_booths_ammount());

    //SynchOut::print("Passenger " + std::to_string(passenger_id) + " is trying to buy ticket to " + destination_station->get_station_name());
    //ustaw w kolejce
    booths[selected_booth_index]->add_passengers_ids(this->passenger_id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::lock_guard<std::mutex> guard(booths[selected_booth_index]->booth_mutex);
    //sprawdź czy jest pociąg do celu z wolnymi miejscami
    
    auto trains = Map::find_trains_to_station(this->actual_station->get_station_id(), this->destination_station->get_station_id());
    if(trains.empty()) {
        booths[selected_booth_index]->remove_passengers_ids(this->passenger_id);
        return 0;
    }

    for (int i = 0; i < trains.size(); i++)
    {
        if (!trains[i]->is_full())
        {
            this->selected_train = trains[i];
            break;
        }
    }

    

    if(this->selected_train == nullptr) {
        booths[selected_booth_index]->remove_passengers_ids(this->passenger_id);
        return 0;
    }
    //SynchOut::print("Passenger " + std::to_string(passenger_id) + " bought ticket for train " + selected_train->get_name());
    selected_train->buy_ticket();
    booths[selected_booth_index]->remove_passengers_ids(this->passenger_id);
    return 1;


}

void Passenger::stop(){
    is_active = false;
}

int Passenger::get_id(){
    return passenger_id;
}