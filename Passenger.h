#pragma once
#include "Station.h"

class Passenger{
    private:
        unsigned int passenger_id;
        Station * actual_station;


        static unsigned int id_counter;

    public:
        Passenger(Station*);
        ~Passenger();               //may cause error, due to actual_station deleting
};