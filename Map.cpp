#include "Map.h"
#include "SynchOut.h"
#include <algorithm>
#include <thread>
#include <iostream>
#include <ncurses.h>
#include <vector>




std::vector<Station*> Map::stations;
std::vector<std::thread*> Map::passenger_threads;
std::vector<std::thread*> Map::train_threads;
std::vector<Train*> Map::trains;
std::vector<Passenger*> Map::passengers;

void Map::create_passenger(int station_id){
    passengers.push_back(new Passenger(stations[station_id]));
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
    train_threads[id]->join();      //TODO: detatch?
}

void Map::simulate(){
    
    std::cout << "Working" << std::endl;

    stations.push_back(new Station("Wroclaw", 5));      //0
    stations.push_back(new Station("Olesnica", 2));     //1
    stations.push_back(new Station("Brzeg", 1));        //2
    stations.push_back(new Station("Olawa", 3));        //3


    create_train("Kosciuszko", 10, {0,1,2,3});
    create_train("Hetman", 10, {3,2,1,0});
    create_train("Kopernik", 10, {1,2,3});
    create_train("Odra", 10, {2,3,0,1,3,1,2,0});


    for (int i = 0; i < 5; i++)
    {
        create_passenger(i%4);
    }

    
        


    // std::thread th0([t0]{t0->exist();});
    // std::thread th1([t1]{t1->exist();});
    // std::thread th2([t2]{t2->exist();});
    // std::thread th3([t3]{t3->exist();});

    std::string stop = "x";

    while (true)
    {
        std::cin >> stop;
        //std::cout << stop << std::endl;
        if (stop == "q")
        {   
            SynchOut::print("**********QUIT**********");
           

            for (int i = 0; i < 5; i++)
            {
                stop_passenger(i);
            }

            for (int i = 0; i < 4; i++)
            {
                stop_train(i);
            }
            
            
            return;
        }
        else
        {
            int ind = std::stoi(stop);
            stop_train(ind);
            SynchOut::print("Stop success.");
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

std::vector<Train*> Map::find_trains_to_station(unsigned int station_id){

    std::vector<Train*> trains_to_station;
    for (int i = 0; i < trains.size(); i++)
    {

        if(!trains[i]->is_routing()) continue;

        auto r = trains[i]->get_route();
        if (std::find(r.begin(), r.end(), station_id) != r.end() )
        {
            trains_to_station.push_back(trains[i]);
        }
        
    }
    return trains_to_station;      

};