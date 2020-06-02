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

    public:

        static void simulate();
        static Station *find_station(unsigned int);
        static std::vector<Train*> find_trains_to_station(unsigned int);

};