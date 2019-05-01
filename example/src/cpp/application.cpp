#include <map>
#include "application.h"

int main(int argc, char* argv[]) {
    Application application;
    showBanner();
    HttpServer httpServer(
        application.getName(),
        application.getProperty<unsigned int>("server.port")
    );
    httpServer.start();
    
    return 0;
}