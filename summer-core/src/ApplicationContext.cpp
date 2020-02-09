/* Created by Tenton Lien on 12/12/2019 */

#include <sstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <LogManager.h>
#include <org/summerframework/data/io.h>
#include "ApplicationContext.h"

ApplicationContext::ApplicationContext() {
    this -> loadData();
    this -> showBanner();
    pid_t pid = getpid();
    std::ostringstream oss;
    oss << "Starting application on " << SystemInfo::getHostName() << " with PID " << pid;
    this -> logManager.setServerName(this -> applicationName);
    this -> logManager.addInfo("org.summerframework.core.Application", oss.str());
}


// Application name
std::string ApplicationContext::getApplicationName() {
    return this -> applicationName;
}

void ApplicationContext::setApplicationName(std::string applicationName) {
    this -> applicationName = applicationName;
}


// Application property
std::string ApplicationContext::getApplicationProperty(std::string applicationPropertyKey) {
    auto propertyIterator = this -> applicationProperties.find(applicationPropertyKey);
    if (propertyIterator == applicationProperties.end()) {
        return 0;  // Property not found
    } else {
        std::istringstream iss(propertyIterator -> second);
        std::string returnValue;
        iss >> returnValue;
        return returnValue;
    }
}


void ApplicationContext::setApplicationProperty(std::string applicationPropertyKey, std::string applicationPropertyValue) {
    this -> applicationProperties.insert({applicationPropertyKey, applicationPropertyValue});
}

void* ApplicationContext::getController() {

}