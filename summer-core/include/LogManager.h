/* Created by Tenton Lien on 12/12/2019 */

#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <string>

class LogManager {
  public:
    void setServerName(std::string);
    void addInfo(std::string, std::string);
    void addWarning(std::string, std::string);
    void addError(std::string, std::string);
    void addFatalError(std::string, std::string);
    std::string getCurrentTime();

  private:
    std::string serverName;    
};

#endif