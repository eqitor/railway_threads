#pragma once
#include <iostream>
#include <mutex>
#include <ncurses.h>

class SynchIO {

    static std::mutex out_mutex;

    public:

    static void print(std::string);
    static void swrefresh(WINDOW*);
};