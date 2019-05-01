/* Created by Tenton Lien on 4/15/2019 */

#include <ctime>
#include <iostream>
#include <sys/timeb.h>

#include "web.h"

void LogManager::setServerName(std::string serverName) {
    this -> serverName = serverName;
}


std::string LogManager::getCurrentTime() {
    time_t t = time(NULL);
    struct timeb tb;
    ftime(&tb);
	char buf[64];
	strftime(buf, 64, "%Y-%m-%d %X", localtime(&t));
    sprintf(buf, "%s.%03d", buf, tb.millitm);
    std::string timeString(buf);
    return timeString;
}


void LogManager::addInfo(std::string info) {
    std::cout << this -> getCurrentTime() << " " <<
                // Yellow
                "\033[40;33m" << "info" << "\033[0m " <<
                "[ " << this -> serverName << " ] " <<
                "\033[40;1;36m" << info << ".\033[0m" << std::endl;
}


void LogManager::addWarning(std::string warn) {
    std::cout << this -> getCurrentTime() << " " <<
                // Purple
                "\033[40;1;35m" << "warn" << "\033[0m " <<
                "[ " << this -> serverName << " ] " <<
                "\033[40;1;36m" << warn << ".\033[0m" << std::endl;
}


void LogManager::addError(std::string error) {
    std::cout << this -> getCurrentTime() << " " <<
                // Red
                "\033[40;1;31m" << "error" << "\033[0m " <<
                "[ " << this -> serverName << " ] " <<
                "\033[40;1;36m" << error << ".\033[0m" << std::endl;
}


void LogManager::addFatalError(std::string fatalError) {
    this -> addError(fatalError);
    exit(-1);
}