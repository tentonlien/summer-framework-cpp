/* Summer: A C++ MVC Framework for Web Application on Linux Server */
/* Summer: Linux服务器上的C++网络应用MVC框架 */
/* Created by Tenton Lien on 4/6/2019 */

#include <cstdlib>
#include <iostream>
#include "summer.h"
#include "xml/tinyxml2.h"
#include <time.h>
#include <vector>

// Global params
std::string param_app_name;
unsigned int param_app_port;

char* param_mysql_host;
unsigned int param_mysql_port;
char* param_mysql_user;
char* param_mysql_password;

extern void httpResponse();

// Load config/app.xml
int loadConfig() {
    tinyxml2::XMLDocument doc;

    if(doc.LoadFile("config/app.xml")) {
        printLog(Logs.ERROR, doc.ErrorStr());
        return -1;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement();
    if(root == NULL) {
        printLog(Logs.ERROR, "Failed to load file: No root element");
        doc.Clear();
        return -1;
    }

    for(tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "app") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "name") {
                    param_app_name = subElem -> FirstChild() -> ToText() -> Value();
                } else if (subElemName == "port") {
                    param_app_port = std::atoi(subElem -> FirstChild() -> ToText() -> Value());
                }
            }
        } else if (elemName == "mysql") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "host") {
                    param_mysql_host = (char*)(subElem -> FirstChild() -> ToText() -> Value());
                } else if (subElemName == "port") {
                    param_mysql_port = std::atoi(subElem -> FirstChild() -> ToText() -> Value());
                } else if (subElemName == "user") {
                    param_mysql_user = (char*)(subElem -> FirstChild() -> ToText() -> Value());
                } else if (subElemName == "password") {
                    param_mysql_password = (char*)(subElem -> FirstChild() -> ToText() -> Value());
                }
            }
        }
    }
    doc.Clear();
    return 0;
}


void printLog(Log logType, std::string logContent) {
    time_t tt = time(NULL);
    tm* t= localtime(&tt);

    std::cout << t -> tm_year + 1900 << "-" <<
                t -> tm_mon + 1 << "-" <<
                t -> tm_mday << " " <<
                t -> tm_hour << ":" <<
                t -> tm_min / 10 << t -> tm_min % 10 << ":" <<
                t -> tm_sec / 10 << t -> tm_sec % 10 << " " <<
                "[ " << param_app_name << " ] " <<
                logType << ": " <<
                logContent << "." << std::endl;
}


int main() {
    // Initial configuration
    loadConfig();

    // Print startup info on screen
    printLog(Logs.INFO, "Summer web app listens at port " + std::to_string(param_app_port));
    
    httpResponse();
    return 0;
}