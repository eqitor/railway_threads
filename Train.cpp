#include "Train.h"

unsigned int Train::id_counter = 0;

Train::Train(std::string name, unsigned int capacity, const std::initializer_list<unsigned int> route_array){

    train_id = ++id_counter;
    name = name;
    capacity = capacity;
    route = route_array;
    route.insert(route.end(), route_array.begin(), route_array.end());
}

Train::~Train(){
    route.clear();
}