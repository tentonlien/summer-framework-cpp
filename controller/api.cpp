#include <time.h>
#include "../summer/summer.h"

std::string _info(Method method, std::string data) {
    if (method == Methods.GET) {
        return "GET";
    } else {
        return "Invalid Request Method";
    }
}


std::string _user(Method method, std::string data) {
    Sql sql("demo_db");
    sql.query("select * from demo_table");
    std::string res = "";

    for (int i = 0; i < sql.result.size(); i ++) {
        for (int k = 0; k < sql.result.at(i).size(); k ++) {
            res += sql.result.at(i).at(k) + " ";
        }
        res += "<br/>";
    }

    return res;
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