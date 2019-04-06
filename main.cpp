/* Summer: A C++ MVC Framework for Web Application on Linux Server */
/* Summer: Linux服务器上的C++网络应用MVC框架 */
/* Created on Apr.6, 2019 */

#include <cstdlib>
#include <iostream>
#include "summer/summer.h"
#include "summer/xml/tinyxml2.h"
#include <time.h>

// Global params
std::string PARAM_APP_NAME;
unsigned int PARAM_APP_PORT;

std::string PARAM_MYSQL_HOST;
std::string PARAM_MYSQL_USERNAME;
std::string PARAM_MYSQL_PASSWORD;

extern void httpResponse();

// Load config/app.xml
int loadConfig() {
    tinyxml2::XMLDocument doc;

    if(doc.LoadFile("config/app.xml")) {
        std::cerr << doc.ErrorStr() << std::endl;
        return -1;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return -1;
    }

    for(tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "app") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "name") {
                    PARAM_APP_NAME = subElem -> FirstChild() -> ToText() -> Value();
                } else if (subElemName == "port") {
                    PARAM_APP_PORT = std::atoi(subElem -> FirstChild() -> ToText() -> Value());
                }
            }
        } else if (elemName == "mysql") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "host") {
                    PARAM_MYSQL_HOST = subElem -> FirstChild() -> ToText() -> Value();
                } else if (subElemName == "username") {
                    PARAM_MYSQL_USERNAME = std::atoi(subElem -> FirstChild() -> ToText() -> Value());
                } else if (subElemName == "password") {
                    PARAM_MYSQL_PASSWORD = std::atoi(subElem -> FirstChild() -> ToText() -> Value());
                }
            }
        }
    }
    doc.Clear();
    return 0;
}


int main() {
    // Initial configuration
    loadConfig();

    // Print startup info on screen
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    std::cout << t -> tm_year + 1900 << "-" <<
                t -> tm_mon + 1 << "-" <<
                t -> tm_mday << " " <<
                t -> tm_hour << ":" <<
                t -> tm_min / 10 << t -> tm_min % 10 << ":" <<
                t -> tm_sec / 10 << t -> tm_sec % 10 << " " <<
                "[ " << PARAM_APP_NAME << " ] " <<
                "Summer web app listens at port " << PARAM_APP_PORT << "." << std::endl;
    
    httpResponse();
    return 0;
}