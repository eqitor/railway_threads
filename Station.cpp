#include "Station.h"
#include "TicketBooth.h"
#include <string>

unsigned int Station::id_counter = 0;

Station::Station(std::string name, unsigned int booth_ammount){
    station_id = ++id_counter;
    name = name;
    
    for (int i = 0; i < booth_ammount; i++)
    {
        booths_vector.push_back(TicketBooth());
    }
    
}


Station::~Station(){
    booths_vector.clear();
}