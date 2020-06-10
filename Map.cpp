#include "Map.h"
#include "SynchOut.h"
#include <algorithm>
#include <thread>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <atomic>




std::vector<Station*> Map::stations;
std::vector<std::thread*> Map::passenger_threads;
std::vector<std::thread*> Map::train_threads;
std::vector<Train*> Map::trains;
std::vector<Passenger*> Map::passengers;
GUI* Map::gui = new GUI();

void Map::create_passenger(int station_id, GUI *gui){
    passengers.push_back(new Passenger(stations[station_id], gui));
    Passenger *temp = passengers.back();
    std::thread* temp_thread = new std::thread([temp]{temp->exist();});
    passenger_threads.push_back(temp_thread);

}

void Map::stop_passenger(int passenger_id){
    passengers[passenger_id]->stop();
    passenger_threads[passenger_id]->join();
}

void Map::create_train(std::string name, unsigned int capacity, const std::initializer_list<unsigned int> route_array){
    trains.push_back(new Train(name, capacity, route_array));
    Train *temp = trains.back();
    std::thread* temp_thread = new std::thread([temp]{temp->exist();});
    train_threads.push_back(temp_thread);
}


void Map::stop_train(int id){
    trains[id]->stop();
    train_threads[id]->join();      
}



void Map::simulate(){
    

    int PASSENGERS = 10;

    std::cout << "Workingg" << std::endl;

    stations.push_back(new Station("Wroclaw", 3));      //0
    stations.push_back(new Station("Olesnica", 2));     //1
    stations.push_back(new Station("Brzeg", 1));        //2
    stations.push_back(new Station("Olawa", 3));        //3
    stations.push_back(new Station("Opole", 2));        //4
    stations.push_back(new Station("Walbrzych", 1));    //5
    stations.push_back(new Station("Zielona Gora", 3));        //6
    stations.push_back(new Station("Zagan", 4));        //7

    Map::gui->init();

    GUI* ptr = Map::gui;

    

    create_train("Kosciuszko", 10, {0,6,2});
    create_train("Hetman", 10, {1,5,2,4});
    create_train("Kopernik", 10, {7,3});
    create_train("Odra", 10, {0,2,4});


    for (int i = 0; i < PASSENGERS; i++)
    {
        create_passenger(i%stations.size(),gui);
    }

    std::thread gui_thread([ptr]{ptr->main_loop();});
    

        

    std::string stop = "x";

    while (true)
    {
        std::cin >> stop;
        if (stop == "q")
        {   
            SynchOut::print("**********QUIT**********");
           

            for (int i = 0; i < passengers.size(); i++)
            {
                stop_passenger(i);
            }

            for (int i = 0; i < trains.size(); i++)
            {
                stop_train(i);
            }
            
            
            return;
        }
        else if(std::stoi(stop) >=0 && std::stoi(stop) < trains.size()-1)
        {
            if (trains[std::stoi(stop)]->is_routing())
            {
                SynchOut::print("**********STOP TRAIN**********");
                stop_train(std::stoi(stop));
            }
            else
            {
                SynchOut::print("**********STOP TRAIN**********");
                stop_train(std::stoi(stop));
            }
            
            
            
        }
        
    }
    
    




};

Station* Map::find_station(unsigned int station_id){

    for (int i = 0; i < stations.size(); i++)
    {
        if (stations[i]->get_station_id() == station_id)
        {
            return stations[i];
        }
        
    }
    return nullptr;
    
};

std::vector<Train*> Map::find_trains_to_station(unsigned int act_station_id, unsigned int dest_station_id){

    std::vector<Train*> trains_to_station;
    for (int i = 0; i < trains.size(); i++)
    {

        if(!trains[i]->is_routing()) continue;

        auto r = trains[i]->get_route();
        if (std::find(r.begin(), r.end(), act_station_id) != r.end() && std::find(r.begin(), r.end(), dest_station_id) != r.end())
        {
            trains_to_station.push_back(trains[i]);
        }
        
    }
    return trains_to_station;      

};