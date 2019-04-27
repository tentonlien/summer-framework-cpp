#ifndef APPLICATION_H
#define APPLICATION_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "summer.h"
#include "sql.h"
#include "web.h"

#include <map>
#include <sstream>
#include <string>

class Application {
    public:
        Application();

        template<class Type>
        Type getProperty(std::string propertyName) {
             auto propertyIterator = this -> properties.find(propertyName);
             if (propertyIterator == properties.end()) {
                 return 0;  // Property not found
             } else {
                 std::istringstream iss(propertyIterator -> second);
                 Type returnValue;
                 iss >> returnValue;
                 return returnValue;
             }
        }

        void setProperties(std::map<std::string, std::string> properties) {
            this -> properties = properties;
        }

        void addObject(void (*pfun)()) {
            this -> objects.push_back(pfun);
        }

        void setName(std::string name) {
            this -> name = name;
        }

        std::string getName() {
            return this -> name;
        }

        void setModules(std::vector<std::string> modules) {
            this -> modules = modules;
        }

        bool existModule(std::string module) {
            auto iterator = find(this -> modules.begin(), this -> modules.end(), module);
            if (iterator != this -> modules.end()) {
                return true;
            }
            return false;
        }
    
    private:
        std::string name;
        std::map<std::string, std::string> properties;
        std::vector<std::string> modules;
        std::vector<void (*)()> objects;
};

extern void showBanner();
extern Application application;

#endif