#include "Station.h"
#include "SynchIO.h"
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

Station::Station(std::string name, unsigned int booth_ammount, int x, int y){
    station_id = id_counter++;
    this->name = name;
    
    for (int i = 0; i < booth_ammount; i++)
    {
        booths_vector.push_back(new TicketBooth());
    }

    draw();

    
}

int Station::get_booths_ammount(){
    return booths_vector.size();
}

std::vector<TicketBooth*> Station::get_booths_vector(){
    return booths_vector;
}



void Station::draw(){
    win = newwin(20,10,1,1+10*station_id);
    box(win,0,0);
    SynchIO::swrefresh(win);
}

Station::Station(){};

Station::~Station(){
    booths_vector.clear();
}