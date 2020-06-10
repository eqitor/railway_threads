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

int Station::get_booths_ammount(){
    return booths_vector.size();
}

std::vector<TicketBooth*> Station::get_booths_vector(){
    return booths_vector;
}

void Station::add_visitor(int id){
    visitors_ids.push_back(id);
}

void Station::remove_visitor(int id){
    for (int i = 0; i < visitors_ids.size(); i++)
    {
        if (visitors_ids[i] == id)
        {
            visitors_ids.erase(visitors_ids.begin()+i);
        }
        
    }
    

}


std::string Station::get_visitors_string(){
    // std::stringstream ss;
    // std::copy(visitors_ids.begin(), visitors_ids.end(), std::ostream_iterator<int>(ss," "));
    // std::string format = ss.str();
    return "x"; //format.substr(0, format.length()-1);
}

Station::Station(){};

Station::~Station(){
    booths_vector.clear();
}