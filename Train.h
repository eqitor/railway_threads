#pragma once

#include <string>
#include <vector>
#include <condition_variable>
#include "SynchIO.h"
#include "Station.h"
#include "Map.h"

/*Representation of train.*/
class Train{
    
    private:
        unsigned int train_id;
        std::string name;
        unsigned int capacity;
        unsigned int passengers;
        unsigned int tickets;
        bool is_active;

        std::vector<unsigned int> route;
        unsigned int route_size;

        unsigned int current_dest;

        static unsigned int id_counter;

    public:
        Station *next_station;  //zrobić getter
        std::mutex train_mutex;
        std::condition_variable train_cv;
        std::vector<unsigned int> get_route();
        void exist();
        void stop();
        bool is_full();
        void get_in();
        void get_out();
        void buy_ticket();
        void free_ticket();
        std::string get_name();
        bool is_routing();
        Train(std::string, unsigned int, const std::initializer_list<unsigned int>);
        Train();
        ~Train();

};