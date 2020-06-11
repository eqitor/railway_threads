#pragma once
#include "TicketBooth.h"
#include <string>
#include <vector>
#include <mutex>
#include <sstream>
#include <iterator>
#include "Passenger.h"

class TicketBooth;


class Station{
    private:

        unsigned int station_id;
        std::string name;

        std::vector<TicketBooth*> booths_vector;

        static unsigned int id_counter;

        std::vector<int> visitors_ids;
        std::vector<int> platform_ids;

        friend class GUI;

    public:

        std::mutex mutex;
        std::mutex station_get_mutex;

        static unsigned int get_stations_ammount();
        int get_booths_ammount();
        unsigned int get_station_id();
        std::string get_station_name();
        std::vector<TicketBooth*> get_booths_vector();
        void add_visitor(int id);
        void remove_visitor(int id);
        std::string get_visitors_string();
        void add_platform_id(int id);
        void remove_platform_id(int id);
        std::string get_platform_string();
        std::vector<std::string> get_station_info();
        Station(std::string, unsigned int);
        Station();
        ~Station();
};