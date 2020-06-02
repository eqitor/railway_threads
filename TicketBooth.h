
#pragma once
#include <vector>
#include <mutex>

/*Representation of ticket booth.*/
class TicketBooth{



    public:


        std::mutex booth_mutex;
        TicketBooth();
        ~TicketBooth();



};