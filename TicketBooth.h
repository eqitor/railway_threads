
#pragma once
#include <vector>
#include <mutex>
#include <sstream>
#include <iterator>

/*Representation of ticket booth.*/
class TicketBooth{

    std::vector<int> passengers_ids;
    
    friend class GUI;

    public:

        

        std::mutex booth_mutex;
        std::mutex booth_mutex_2;
        void add_passengers_ids(int id);
        void remove_passengers_ids(int id);
        std::string get_passengers_string();
        TicketBooth();
        ~TicketBooth();



};