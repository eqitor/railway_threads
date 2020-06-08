#pragma once
#include <iostream>
#include <mutex>
class SynchOut {

    static std::mutex out_mutex;

    public:

    static void print(std::string);
};