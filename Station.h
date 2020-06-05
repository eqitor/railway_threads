#pragma once
#include "TicketBooth.h"
#include <string>
#include <vector>
#include <mutex>
#include <ncurses.h>

class TicketBooth;


class Station{
    private:

        unsigned int station_id;
        std::string name;

        std::vector<TicketBooth*> booths_vector;

        static unsigned int id_counter;

        WINDOW * win;

        

    public:

        std::mutex mutex;

        static unsigned int get_stations_ammount();
        int get_booths_ammount();
        unsigned int get_station_id();
        std::string get_station_name();
        std::vector<TicketBooth*> get_booths_vector();

        void draw();

        Station(std::string, unsigned int, int, int);
        Station();
        ~Station();
};