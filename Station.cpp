#include "Station.h"
#include <string>

unsigned int Station::id_counter = 0;


unsigned int Station::get_stations_ammount(){
    return Station::id_counter;
};


unsigned int Station::get_station_id(){
    return station_id;
};


std::string Station::get_station_name(){
    return name;
};

Station::Station(std::string name, unsigned int booth_ammount){
    station_id = id_counter++;
    this->name = name;
    
    for (int i = 0; i < booth_ammount; i++)
    {
        booths_vector.push_back(new TicketBooth());
    }
    
}

std::vector<TicketBooth*> Station::get_booths_vector(){
    return booths_vector;
}

Station::Station(){};

Station::~Station(){
    booths_vector.clear();
}