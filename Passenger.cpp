#include "Passenger.h"

unsigned int Passenger::id_counter = 0;

Passenger::Passenger(Station * start_station){
    
    passenger_id = ++id_counter;
    actual_station = start_station;
};

Passenger::~Passenger(){};