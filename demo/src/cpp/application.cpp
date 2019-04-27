#include <map>
#include "application.h"

Application application;

int main(int argc, char* argv[]) {

    // void (*pfun)();
    // application.addModule();
    showBanner();
    HttpServer httpServer(
        application.getName(),
        application.getProperty<unsigned int>("server.port")
    );
    httpServer.start();
    
    return 0;
}