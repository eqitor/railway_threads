#include "TicketBooth.h"

void TicketBooth::add_passengers_ids(int id){
    std::lock_guard<std::mutex> g(booth_mutex_2);
    for (int i = 0; i < passengers_ids.size(); i++)
    {
        if(passengers_ids[i] == id) return;
    }
    
    passengers_ids.push_back(id);
}

void TicketBooth::remove_passengers_ids(int id){
    std::lock_guard<std::mutex> g(booth_mutex_2);
    for (int i = 0; i < passengers_ids.size(); i++)
    {
        if (passengers_ids[i] == id)
        {
            passengers_ids.erase(passengers_ids.begin()+i);
        }
        
    }
    

}



std::string TicketBooth::get_passengers_string(){
    std::lock_guard<std::mutex> g(booth_mutex_2);
    std::stringstream ss;
    std::copy(passengers_ids.begin(), passengers_ids.end(), std::ostream_iterator<int>(ss," "));
    std::string format = ss.str();
    return format.substr(0, format.length()-1);
}

TicketBooth::TicketBooth(){};
TicketBooth::~TicketBooth(){};


