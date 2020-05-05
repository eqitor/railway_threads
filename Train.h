#pragma once

#include <string>
#include <vector>

/*Representation of train.*/
class Train{
    
    private:
        unsigned int train_id;
        std::string name;
        unsigned int capacity;
        unsigned int passengers;

        std::vector<unsigned int> route;
        unsigned int route_size;

        static unsigned int id_counter;

    public:
        Train(std::string, unsigned int, const std::initializer_list<unsigned int>);
        ~Train();

};