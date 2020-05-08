// #include "Station.h"
// #include "Passenger.h"
// #include "TicketBooth.h"
// #include "Train.h"
#include "Map.h"
#include <iostream>


using namespace std;


int main(){

    // Station *station = new Station("Zamosc Starowka",5);
    // Train *train = new Train("Hetman",10,{1,2,3,4});
    // Passenger *passenger = new Passenger(station);

    // delete station;
    // delete train;
    // delete passenger;

    // Map *map = new Map();
    // map->simulate();
    // delete map;

    Map::simulate();

}