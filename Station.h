#pragma once
#include "TicketBooth.h"
#include <string>
#include <vector>


class Station{
    private:
        unsigned int station_id;
        std::string name;

        std::vector<TicketBooth> booths_vector;

        static unsigned int id_counter;

    public:
        Station(std::string, unsigned int);
        ~Station();
};