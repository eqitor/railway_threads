#include "Map.h"
#include <algorithm>
#include <thread>
#include <iostream>
#include <ncurses.h>

std::vector<Station*> Map::stations;
std::vector<Train*> Map::trains;
std::vector<Passenger*> Map::passengers;

void Map::simulate(){
    
    std::cout << "Working" << std::endl;
    stations.push_back(new Station("Wroclaw", 5));      //0
    stations.push_back(new Station("Olesnica", 2));     //1
    stations.push_back(new Station("Brzeg", 1));        //2
    stations.push_back(new Station("Olawa", 3));        //3


    trains.push_back(new Train("Kosciuszko", 10, {0,1,2,3}));
    trains.push_back(new Train("Hetman", 10, {3,2,1,0}));
    trains.push_back(new Train("Kopernik", 10, {1,2,3}));
    trains.push_back(new Train("Odra", 10, {2,3,0,1,3,1,2,0}));

    

    Train *t0 = trains[0];
    Train *t1 = trains[1];
    Train *t2 = trains[2];
    Train *t3 = trains[3];
    
    std::thread th0([t0]{t0->exist();});
    std::thread th1([t1]{t1->exist();});
    std::thread th2([t2]{t2->exist();});
    std::thread th3([t3]{t3->exist();});

    std::string stop = "x";

    while (true)
    {
        std::cin >> stop;
        //std::cout << stop << std::endl;
        if (stop == "q")
        {
            t0->stop();
            t1->stop();
            t2->stop();
            t3->stop();


            th0.join();
            th1.join();
            th2.join();
            th3.join();
            return;
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

Train* Map::find_train_to_station(unsigned int station_id){

    for (int i = 0; i < trains.size(); i++)
    {
        auto r = trains[i]->get_route();
        if (std::find(r.begin(), r.end(), station_id) != r.end() )
        {
            return trains[i];
        }
        
    }
    return nullptr;      

};