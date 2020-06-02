#include "Passenger.h"
#include <condition_variable>
unsigned int Passenger::id_counter = 0;

Passenger::Passenger(Station* start_station){
    
    passenger_id = id_counter++;
    actual_station = start_station;
};

Passenger::Passenger(){};

Passenger::~Passenger(){};

void Passenger::exist(){

    while (true)
    {
        //wybierz cel
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        std::cout << "Passenger " << passenger_id << " is visiting " << actual_station->get_station_name() << std::endl;
        set_destination();
        //ustaw sie do budki - kup bilet
        int buy_success = try_buy_ticket();

        if(!buy_success) continue;
        //czekaj na pociąg
        std::cout << "Passenger " << passenger_id << " is waiting for train " << selected_train->get_name() << std::endl;
        std::unique_lock<std::mutex> lk(selected_train->train_mutex);
        selected_train->train_cv.wait(lk, [&]{return actual_station->get_station_id() == selected_train->next_station->get_station_id();});
        //wsiądź jedź i wysiądź na stacji
        this->selected_train->get_in();
        //jedz
        selected_train->train_cv.wait(lk, [&]{return destination_station->get_station_id() == selected_train->next_station->get_station_id();});
        //wysiadam
        this->selected_train->get_out();
        this->actual_station = this->destination_station;
        
    }
    
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

    static thread_local std::uniform_int_distribution<> wait(0, booths.size());
    int selected_booth_index = wait(range);

    std::cout << "Passenger " << passenger_id << " is trying to buy ticket to " << destination_station->get_station_name() << std::endl;
    //ustaw w kolejce
    std::lock_guard<std::mutex> guard(booths[selected_booth_index]->booth_mutex);
    //sprawdź czy jest pociąg do celu z wolnymi miejscami
    auto trains = Map::find_trains_to_station(this->destination_station->get_station_id());
    if(trains.empty()) return 0;

    for (int i = 0; i < trains.size(); i++)
    {
        if (!trains[i]->is_full())
        {
            this->selected_train = trains[i];
            break;
        }
    }

    if(this->selected_train == nullptr) return 0;
    std::cout << "Passenger " << passenger_id << " bought ticket for train " << selected_train->get_name() << std::endl;
    return 1;


}