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
        std::unique_lock<std::mutex> train_lk(train_mutex);     //blokuje

        next_station = Map::find_station(route[current_dest]);
        SynchOut::print("Train " + this->name + ", ID: " + std::to_string(train_id) + " is traveling to " + next_station->get_station_name()
                    + " ID " + std::to_string(route[current_dest]));

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        

        /*try access to Station*/
        SynchOut::print("Train " + name + ", ID: " + std::to_string(train_id) + " is waiting for access to " + next_station->get_station_name()
                    + " ID " + std::to_string(route[current_dest]));


         

        std::unique_lock<std::mutex> guard(next_station->mutex, std::defer_lock);
        SynchOut::print("Train " + name + ", ID: " + std::to_string(train_id) + " is on station " + next_station->get_station_name()
                    + " ID " + std::to_string(route[current_dest]));

        guard.lock();
        
        train_lk.unlock();      //odblokuj
        train_cv.notify_all();  //powiadom

        

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        

        guard.unlock();


        train_lk.lock();    //zablokuj

        
        current_dest++;


        if (current_dest == route_size-1)
        {
            current_dest = 0;
        }

        
        
    }
    

}

bool Train::is_full(){
    if(capacity-passengers == 0) return true;
    return false;
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

void Train::get_in(){
    this->passengers++;
}

void Train::get_out(){
    this->passengers--;
}

std::string Train::get_name(){
    return name;
}

Train::Train(){};


Train::~Train(){
    route.clear();
}