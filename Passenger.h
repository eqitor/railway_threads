#pragma once
#include <random>
#include <chrono>
#include <thread>
#include <iostream>
#include "SynchOut.h"
#include "Station.h"
#include "Map.h"
#include "Train.h"

class Train;

class Passenger{
    private:
        unsigned int passenger_id;
        Station * actual_station;
        Station * destination_station;
        std::mt19937 range{ std::random_device{}() };
        Train *selected_train;
        bool is_active;


        static unsigned int id_counter;

    public:
        Passenger(Station*);
        Passenger();
        ~Passenger();               //may cause error, due to actual_station deleting

        void exist();
        void set_destination();
        bool try_buy_ticket();
        void stop();
};
