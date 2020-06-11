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
    std::lock_guard<std::mutex> g(station_get_mutex);
    return booths_vector.size();
}

std::vector<TicketBooth*> Station::get_booths_vector(){
    std::lock_guard<std::mutex> g(station_get_mutex);
    return booths_vector;
}

void Station::add_visitor(int id){
    std::lock_guard<std::mutex> g(station_get_mutex);
    for (int i = 0; i < visitors_ids.size(); i++)
    {
        if(visitors_ids[i] == id) return;
    }
    
    visitors_ids.push_back(id);
}

void Station::remove_visitor(int id){
    std::lock_guard<std::mutex> g(station_get_mutex);
    for (int i = 0; i < visitors_ids.size(); i++)
    {
        if (visitors_ids[i] == id)
        {
            visitors_ids.erase(visitors_ids.begin()+i);
        }
        
    }
    

}



std::string Station::get_visitors_string(){
    //std::lock_guard<std::mutex> g(station_get_mutex);
    std::stringstream ss;
    std::copy(visitors_ids.begin(), visitors_ids.end(), std::ostream_iterator<int>(ss," "));
    std::string format = ss.str();
    return format.substr(0, format.length()-1);
}


void Station::add_platform_id(int id){
    std::lock_guard<std::mutex> g(station_get_mutex);
    for (int i = 0; i < platform_ids.size(); i++)
    {
        if(platform_ids[i] == id) return;
    }
    
    platform_ids.push_back(id);
}

void Station::remove_platform_id(int id){
    std::lock_guard<std::mutex> g(station_get_mutex);
    for (int i = 0; i < platform_ids.size(); i++)
    {
        if (platform_ids[i] == id)
        {
            platform_ids.erase(platform_ids.begin()+i);
        }  
    }

}

std::string Station::get_platform_string(){
    //std::lock_guard<std::mutex> g(station_get_mutex);
    std::stringstream ss;
    std::copy(platform_ids.begin(), platform_ids.end(), std::ostream_iterator<int>(ss," "));
    std::string format = ss.str();
    return format.substr(0, format.length()-1);
}

std::vector<std::string> Station::get_station_info(){
    std::lock_guard<std::mutex> g(station_get_mutex);
    std::vector<std::string> info;
    info.push_back(name);
    info.push_back(get_visitors_string());
    info.push_back(get_platform_string());

    for (int i = 0; i < booths_vector.size(); i++)
    {
        info.push_back(booths_vector[i]->get_passengers_string());
    }
    
    return info;

}


Station::Station(){};

Station::~Station(){
    booths_vector.clear();
}