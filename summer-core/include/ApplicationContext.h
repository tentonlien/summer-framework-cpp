/* Created by Tenton Lien on 12/12/2019 */

#ifndef SUMMER_APPLICATION_H
#define SUMMER_APPLICATION_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "LogManager.h"

class ApplicationContext {
  public:
    LogManager logManager;
    
   ApplicationContext();
    void showBanner();
    void loadData();

    // Application property
    std::string getApplicationProperty(std::string);
    void setApplicationProperty(std::string, std::string);

    // Application name
    std::string getApplicationName();
    void setApplicationName(std::string);

    void* getController();
    

  private:
    std::string applicationName;
    std::string banner;
    std::map<std::string, std::string> applicationProperties;
    std::map<std::string, void*> controllerPointer;

    std::vector<void*> controllerPointers;
    std::vector<void*> modelPointers;

};

extern ApplicationContext applicationContext;

#endif