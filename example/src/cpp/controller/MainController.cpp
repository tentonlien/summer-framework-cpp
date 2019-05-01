#include <time.h>
#include <iostream>
#include "application.h"
#include "../entity/UserEntity.cpp"
#include "sql.h"


using namespace std;

extern string registerService(UserEntity);

/// RestController
class MainController : public Controller
{
  public:
    /// RequestMapping("/user")
    UserEntity getUser() {
        UserEntity user;
        user.setName("Tom");
        user.setPassword("123456");
        return user;
    }

    /// RequestMapping("/info")
    string getInfo() {
        if (request -> method == HttpRequestMethod.GET) {
            return "GET";
        } else {
            return "Invalid Request Method: " + request->method;
        }
    }

    /// RequestMapping("/login")
    std::string getUser2() {
        std::string res = "";
        try {
            MysqlConnector mysqlConnector("mysql://localhost:3306/dbname?user=root&password=xxxxxxxx");
            SqlQueryResult* result = mysqlConnector.executeQuery("SELECT * FROM dbname where condition='true'");
            while (result -> hasNext()) {
                res += result -> getString(4) + " ";
            }
            mysqlConnector.close();
        } catch (exception &e) {
            return e.what();
        }

        return res;
    }

    // Get current system time
    /// RequestMapping("/time")
    string getTime() {
        time_t t = time(NULL);
	    char buf[64];
	    strftime(buf, 64, "%Y-%m-%d %X", localtime(&t));
        string returnData = "<h1>Current Time: ";
        returnData.append(buf).append("</h1>");
        return returnData;
    }
};