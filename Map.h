#pragma once
#include "Station.h"
#include "Train.h"
#include "Passenger.h"
#include <vector>

class Passenger;
class Train;

class Map{

    private:
        static std::vector<Station*> stations;
        static std::vector<Passenger*> passengers;
        static std::vector<Train*> trains;
        static std::vector<std::thread*> passenger_threads;
        static std::vector<std::thread*> train_threads;
        


        static void create_passenger(int);
        static void stop_passenger(int);
        static void create_train(std::string, unsigned int, const std::initializer_list<unsigned int>);
        static void stop_train(int);
        static void Read(std::atomic<bool>&);

    public:

        static void simulate();
        static Station *find_station(unsigned int);
        static std::vector<Train*> find_trains_to_station(unsigned int, unsigned int);

};