#include <time.h>
#include "../summer/summer.h"

std::string _info(Method method, std::string data) {
    return "<h1>Information Page</h1>";
}

std::string _user(Method method, std::string data) {
    return "<h1>Welcome, Dear User!</h1>";
}

// Get current system time
std::string _time(Method method, std::string data) {
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    return "<h1>Current Time: " + 
            std::to_string(t -> tm_year + 1900) + "-" +
            std::to_string(t -> tm_mon + 1) + "-" +
            std::to_string(t -> tm_mday) + " " +
            std::to_string(t -> tm_hour) + ":" +
            std::to_string(t -> tm_min / 10) +  std::to_string(t -> tm_min % 10) + ":" +
            std::to_string(t -> tm_sec / 10) +  std::to_string(t -> tm_sec % 10) +
            "</h1>";
}