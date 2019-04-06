#include <iostream>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "methods.h"
#include <string>
#include "summer.h"
#include <sys/socket.h>
#include <unistd.h>

extern std::string router(Method, std::string);

void httpResponse() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PARAM_APP_PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        valread = read(new_socket, buffer, 1024);

        unsigned int pos = 0;
        std::string methodString, url;

        // Retrieve request method
        while (buffer[pos] != ' ') {
            methodString += buffer[pos];
            pos ++;
        }
        pos ++;

        // Retrieve request URL
        while (buffer[pos] != ' ') {
            url += buffer[pos];
            pos ++;
        }
        Method method(methodString);
        std::string responseString = router(method, url);
        char* response = const_cast<char*>(responseString.c_str());
        
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }
}