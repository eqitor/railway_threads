#include "SynchIO.h"
#include <mutex>
#include <ncurses.h>

std::mutex SynchIO::out_mutex;

void SynchIO::print(std::string text){
    std::lock_guard<std::mutex> guard(out_mutex);
    std::cout << text << std::endl;
}

void SynchIO::swrefresh(WINDOW * win){
    std::lock_guard<std::mutex> guard(out_mutex);
    wrefresh(win);

}