/* Created by Tenton Lien on 4/6/2019 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <regex>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "web.h"

extern void router(HttpRequest*, HttpResponse*);

HttpServer::HttpServer(std::string name, unsigned int port) {
    this -> serverName = name;
    this -> serverPort = port;
    logManager.setServerName(name);
}


void HttpServer::start() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        logManager.addFatalError("Http server creates socket failed");
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        logManager.addFatalError("Http server sets socket failed");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port =htons(this -> serverPort);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        logManager.addFatalError("Http server binds failed");
    }
    
    if (listen(server_fd, 3) < 0) {
        logManager.addFatalError("Http server listens at port failed");
    }

    this -> logManager.addInfo("Summer web app starts to listen at port " + std::to_string(this -> serverPort));

    this -> testDatabaseConnection();

    // Listen and deal with connection
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen)) < 0)
        {
            logManager.addError("Http server accepts connection failed");
        }
        
        valread = read(new_socket, buffer, 1024);

        HttpRequest request(buffer);
        HttpResponse response;
        router(&request, &response);
        std::string temp = response.generate();
        
        send(new_socket, const_cast<char*>(temp.c_str()), temp.length(), 0);
        close(new_socket);
    }
}


void HttpServer::testDatabaseConnection() {
/*     if (true || application.existModule("summer-sql")) {
        // Test DB connection
        // TO-DO
        usleep(800000);

        if (true) {
            logManager.addWarning("Try to connect to database failed");
        }
    } */
}