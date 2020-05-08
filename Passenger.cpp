#include "Passenger.h"
unsigned int Passenger::id_counter = 0;

Passenger::Passenger(Station* start_station){
    
    passenger_id = id_counter++;
    actual_station = start_station;
};

Passenger::Passenger(){};

Passenger::~Passenger(){};

void Passenger::exist(){};

void Passenger::set_destination(){

    unsigned int new_destination_id;
    do{
        static thread_local std::uniform_int_distribution<> wait(0, Station::get_stations_ammount()-1);
        new_destination_id = wait(range);

    } while (new_destination_id == actual_station->get_station_id());
    
    actual_station = Map::find_station(new_destination_id);

};

void Passenger::try_buy_ticket(){
    
}