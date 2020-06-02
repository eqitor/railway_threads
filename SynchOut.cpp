#include "SynchOut.h"
#include <mutex>

std::mutex SynchOut::out_mutex;

void SynchOut::print(std::string text){
    std::lock_guard<std::mutex> guard(out_mutex);
    std::cout << text << std::endl;
}