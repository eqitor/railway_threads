#include "GUI.h"
#include "Map.h"
#include <thread>
#include <chrono>
#include <ctype.h>
#include <algorithm>
#include <sstream>
#include <iterator>

unsigned int GUI::station_box_size_y = 15;
unsigned int GUI::station_box_size_x = 15;
unsigned int GUI::start_point_x = 0;
unsigned int GUI::start_point_y = 0;


std::vector<WINDOW*> GUI::windows;
std::string GUI::visitors_format;


void GUI::main_loop(){

    while (true)
    {
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    
}

void GUI::draw_passanger_on_visitors(int pas_id, int station_id){


    if (!(std::find(stations_state[station_id].begin(), stations_state[station_id].end(), pas_id) != stations_state[station_id].end()))
    {
         stations_state[station_id].push_back(pas_id);  
    }

    

    

}

void GUI::draw(){

    for (int i = 0; i < Map::stations.size(); i++)
    {
        box(windows[i],0,0);
        mvwprintw(windows[i], 1, 1, Map::stations[i]->get_station_name().c_str());
        


        for (int j = 0; j < Map::stations[i]->get_booths_ammount(); j++)
        {
            mvwprintw(windows[i], 2+j, 1,("B" + std::to_string(j)).c_str());
        }
        
        mvwprintw(windows[i], 2+Map::stations[i]->get_booths_ammount()+1, 1, "VISITORS" );

        
        mvwprintw(windows[i], 2+Map::stations[i]->get_booths_ammount()+2, 4, Map::stations[i]->get_visitors_string().c_str() );

        mvwprintw(windows[i], 2+Map::stations[i]->get_booths_ammount()+4, 1, "PLATFORM" );

        wrefresh(windows[i]);
    }
    refresh();
    
}


void GUI::init(){
    initscr();
    cbreak();
    noecho();
    GUI::visitors_format = "";

    

    for (int i = 0; i < Map::stations.size(); i++)
    {
        stations_state[i] = std::vector<int>();
        GUI::windows.push_back(newwin(station_box_size_y,
                                       station_box_size_x,
                                       start_point_y,
                                       start_point_x + i*(station_box_size_x+1)));
}
}

GUI::GUI(){};