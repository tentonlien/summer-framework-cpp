#include <time.h>
#include "../application.h"
#include "../entity/userEntity.h"

using namespace std;

extern string registerService(UserEntity);

string _register(HttpRequest *request, HttpResponse *response)
{
    if (request->method != HttpRequestMethod.POST)
    {
        return "";
    }

    UserEntity user;

    return registerService(user);
}

std::string _info(HttpRequest *request, HttpResponse *response)
{
    if (request->method == HttpRequestMethod.GET)
    {
        return "GET";
    }
    else
    {
        return "Invalid Request Method: " + request->method;
    }
}

std::string _user(HttpRequest *request, HttpResponse *response)
{
    std::string res = "";
    try
    {
        Sql sql("demo_db");
        sql.query("select * from demo_table");

        for (int i = 0; i < sql.result.size(); i++)
        {
            for (int k = 0; k < sql.result.at(i).size(); k++)
            {
                res += sql.result.at(i).at(k) + " ";
            }
            res += "<br/>";
        }
    }
    catch (DatabaseConnectException &e)
    {
        return e.what();
    }

    return res;
}

// Get current system time
std::string _time(HttpRequest *request, HttpResponse *response)
{
    time_t tt = time(NULL);
    tm *t = localtime(&tt);
    return "<h1>Current Time: " +
           std::to_string(t->tm_year + 1900) + "-" +
           std::to_string(t->tm_mon + 1) + "-" +
           std::to_string(t->tm_mday) + " " +
           std::to_string(t->tm_hour) + ":" +
           std::to_string(t->tm_min / 10) + std::to_string(t->tm_min % 10) + ":" +
           std::to_string(t->tm_sec / 10) + std::to_string(t->tm_sec % 10) +
           "</h1>";
}

// ------------- New Style ---------------
class mainController : public Controller
{
  public:
    UserEntity _getUser() {
        UserEntity user;

        if (Controller::request->method != HttpRequestMethod.POST) {
        }

        user.name = "Tom";
        user.gender = "Male";

        return user;
    }

    string _info() {
        if (request->method == HttpRequestMethod.GET) {
            return "GET";
        } else {
            return "Invalid Request Method: " + request->method;
        }
    }

    std::string _user(HttpRequest *request, HttpResponse *response) {
        std::string res = "";
        try {
            Sql sql("demo_db");
            sql.query("select * from demo_table");

            for (int i = 0; i < sql.result.size(); i++) {
                for (int k = 0; k < sql.result.at(i).size(); k++) {
                    res += sql.result.at(i).at(k) + " ";
                }
                res += "<br/>";
            }
        } catch (DatabaseConnectException &e) {
            return e.what();
        }

        return res;
    }

    // Get current system time
    std::string _time(HttpRequest *request, HttpResponse *response) {
        time_t tt = time(NULL);
        tm *t = localtime(&tt);
        return "<h1>Current Time: " +
               std::to_string(t->tm_year + 1900) + "-" +
               std::to_string(t->tm_mon + 1) + "-" +
               std::to_string(t->tm_mday) + " " +
               std::to_string(t->tm_hour) + ":" +
               std::to_string(t->tm_min / 10) + std::to_string(t->tm_min % 10) + ":" +
               std::to_string(t->tm_sec / 10) + std::to_string(t->tm_sec % 10) +
               "</h1>";
    }
};