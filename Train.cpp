#include "Train.h"
#include <iostream> //TODO: remove iostream, after gui implementation
#include <thread>

unsigned int Train::id_counter = 0;


std::vector<unsigned int> Train::get_route(){
    return route;
};

void Train::exist(){

    while (is_active)
    {
        Station *next_station = Map::find_station(route[current_dest]);
        std::cout << "Train " << this->name << ", ID: " << std::to_string(train_id) << " is traveling to " << next_station->get_station_name()
                    << " ID " << std::to_string(route[current_dest]) << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        

        /*try access to Station*/
        std::cout << "Train " + name + ", ID: " + std::to_string(train_id) + " is waiting for access to " + next_station->get_station_name()
                    + " ID " + std::to_string(route[current_dest])<< std::endl;


        {

        std::lock_guard<std::mutex> guard(next_station->mutex);

        std::cout << "Train " + name + ", ID: " + std::to_string(train_id) + " is on station " + next_station->get_station_name()
                    + " ID " + std::to_string(route[current_dest]) << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        current_dest++;


        if (current_dest == route_size-1)
        {
            current_dest = 0;
        }

        }
        
    }
    

}


Train::Train(std::string name, unsigned int capacity, const std::initializer_list<unsigned int> route_array){

    train_id = id_counter++;
    this->name = name;
    this->capacity = capacity;
    route = route_array;
    route.insert(route.end(), route_array.begin(), route_array.end());
    current_dest = 0;
    route_size = route.size();
    is_active = true;
}


void Train::stop(){
    is_active = false;
}

Train::Train(){};


Train::~Train(){
    route.clear();
}