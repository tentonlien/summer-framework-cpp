#include <iostream>
#include <string>
#include "application.h"

Application::Application() {
    this -> properties.insert({"server.port", "8080"});
    this -> properties.insert({"summer.datasource.password", "xxxxxx"});
    this -> properties.insert({"summer.datasource.url", "mysql://localhost:3306"});
    this -> properties.insert({"summer.datasource.username", "root"});

    this -> setName("DemoApplication");
}