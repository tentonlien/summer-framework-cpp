#include <iostream>
#include <org/summerframework/core.h>
#include <org/summerframework/web.h>

ApplicationContext applicationContext;

int main(int argc, char* argv[]) {
    HttpServer httpServer;
    httpServer.start();
    return 0;
}