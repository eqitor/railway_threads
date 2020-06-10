#pragma once
#include "Station.h"
#include <vector>
#include <ncurses.h>

class GUI{

    private:
        static std::vector<WINDOW*> windows;
        static std::vector<int> *stations_state;
        static std::string visitors_format;
        static bool active;
        

        static unsigned int station_box_size_x, station_box_size_y;
        static unsigned int start_point_x, start_point_y;

    public:
        static void main_loop();
        static void init();
        static void draw();
        static void stop();
        GUI();
        ~GUI();
};