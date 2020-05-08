#pragma once

#include <string>
#include <vector>
#include "Station.h"
#include "Map.h"

/*Representation of train.*/
class Train{
    
    private:
        unsigned int train_id;
        std::string name;
        unsigned int capacity;
        unsigned int passengers;
        bool is_active;

        std::vector<unsigned int> route;
        unsigned int route_size;

        unsigned int current_dest;

        static unsigned int id_counter;

    public:

        std::vector<unsigned int> get_route();
        void exist();
        void stop();
        Train(std::string, unsigned int, const std::initializer_list<unsigned int>);
        Train();
        ~Train();

};