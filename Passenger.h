#pragma once
#include <random>
#include <chrono>
#include "Station.h"
#include "Map.h"



class Passenger{
    private:
        unsigned int passenger_id;
        Station * actual_station;
        std::mt19937 range{ std::random_device{}() };


        static unsigned int id_counter;

    public:
        Passenger(Station*);
        Passenger();
        ~Passenger();               //may cause error, due to actual_station deleting

        void exist();
        void set_destination();
        void try_buy_ticket();
};
