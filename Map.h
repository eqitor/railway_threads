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
        static Train *find_train_to_station(unsigned int);

};