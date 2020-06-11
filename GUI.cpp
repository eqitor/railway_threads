#include "GUI.h"
#include "Map.h"
#include <thread>
#include <chrono>
#include <ctype.h>

unsigned int GUI::station_box_size_y = 15;
unsigned int GUI::station_box_size_x = 15;
unsigned int GUI::start_point_x = 0;
unsigned int GUI::start_point_y = 0;
bool GUI::active = true;


std::vector<WINDOW*> GUI::windows;
std::string GUI::visitors_format;


void GUI::main_loop(){

    while (active)
    {   

        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
}



void GUI::draw(){

    

    for (int i = 0; i < Map::stations.size(); i++)
    {
        std::vector<std::string> info = Map::stations[i]->get_station_info();
        static int booths_ammount = info.size()-3;//Map::stations[i]->get_booths_ammount();
        box(windows[i],0,0);
        mvwprintw(windows[i], 1, 1, info[0].c_str());
        


        for (int j = 3; j < info.size(); j++)
        {
            //mvwprintw(windows[i], 2+j, 1, "       ");
            mvwprintw(windows[i], 2+j, 1,("B" + std::to_string(j) + info[j]/*Map::stations[i]->booths_vector[j]->get_passengers_string()*/ ).c_str());
        }
        
        mvwprintw(windows[i], 2+booths_ammount+1, 1, "VISITORS" );
    
        mvwprintw(windows[i], 2+booths_ammount+2, 1, "                   ");

        mvwprintw(windows[i], 2+booths_ammount+2, 1,  info[1].c_str()/*Map::stations[i]->get_visitors_string().c_str()*/ );

        mvwprintw(windows[i], 2+booths_ammount+4, 1, "PLATFORM" );

        mvwprintw(windows[i], 2+booths_ammount+5, 1, info[2].c_str()/*Map::stations[i]->get_platform_string().c_str()*/ );


        wrefresh(windows[i]);
    }
    refresh();
    
}


void GUI::init(){
    initscr();
    cbreak();
    noecho();

    

    for (int i = 0; i < Map::stations.size(); i++)
    {
        GUI::windows.push_back(newwin(station_box_size_y,
                                       station_box_size_x,
                                       start_point_y,
                                       start_point_x + i*(station_box_size_x+1)));
    }
}

void GUI::stop(){

    GUI::active = false;
}

GUI::GUI(){};