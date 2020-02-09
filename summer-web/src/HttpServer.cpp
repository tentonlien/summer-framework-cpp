/* Created by Tenton Lien on 4/6/2019 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>
#include <netinet/in.h>
#include <regex>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/timeb.h>
#include <unistd.h>

#include "ThreadPool.h"
#include "HttpServer.h"

extern void router(HttpRequest*, HttpResponse*);

std::mutex mtx;

struct Entity {
    int sockfd;
    struct sockaddr_in client;
};


void handle(struct Entity entity) {
    char buffer[1024] = {0};
    int valueRead = read(entity.sockfd, buffer, 1024);
    if (valueRead > 0) {
        HttpRequest request(buffer);
        HttpResponse response;
        router(&request, &response);
        std::string temp = response.generate();
        
        send(entity.sockfd, const_cast<char*>(temp.c_str()), temp.length(), 0);

        if (mtx.try_lock()) {
            time_t t = time(NULL);
            struct timeb tb;
            ftime(&tb);
	        char buf[64];
	        strftime(buf, 64, "%Y-%m-%d %X", localtime(&t));
            sprintf(buf, "%s.%03d", buf, tb.millitm);
            std::string timeString(buf);

            std::ofstream ofs("log/service.txt", std::ios::app);
            ofs << timeString << " " << request.method << " " << request.uri<< std::endl << "Response Body: " << response.getResponseBody() << std::endl << std::endl;
            ofs.close();
            mtx.unlock();
        }
    }
    close(entity.sockfd);
}


HttpServer::HttpServer() {
    this -> serverName = applicationContext.getApplicationName();

    std::stringstream ss;
    int port;
    ss << applicationContext.getApplicationProperty("server.port");
    ss >> port;
    this -> serverPort = port;

    applicationContext.logManager.setServerName(this -> serverName);
}


void HttpServer::start() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        applicationContext.logManager.addFatalError("org.summerframework.web.HttpServer", "Http server creates socket failed");
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        applicationContext.logManager.addFatalError("org.summerframework.web.HttpServer", "Http server sets socket failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this -> serverPort);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        applicationContext.logManager.addFatalError("org.summerframework.web.HttpServer", "Http server binds failed");
    }
    
    if (listen(server_fd, 200) < 0) {
        applicationContext.logManager.addFatalError("org.summerframework.web.HttpServer", "Http server listens at port failed");
    }

    applicationContext.logManager.addInfo("org.summerframework.web.HttpServer", "HttpServer initialized with port(s): " + std::to_string(this -> serverPort) + " (http)");

    this -> testDatabaseConnection();

    ThreadPool pool(200);

    // Listening and dealing with connection
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen)) < 0)
        {
            applicationContext.logManager.addError("Summer.Web.HttpServer", "Http server accepts connection failed");
        }
        struct Entity entity;
        entity.client = address;
        entity.sockfd = new_socket;

        pool.enqueue(handle, entity);
    }
}


void HttpServer::testDatabaseConnection() {
/*     
    if (true || application.existModule("summer-sql")) {
        // Test DB connection
        // TO-DO
        usleep(1000000);

        if (true) {
            logManager.addWarning("Try to connect to database failed");
        }
    } 
*/
}