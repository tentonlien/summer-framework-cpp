/* Created by Tenton Lien on 4/6/2019 */

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>

#include <org/summerframework/core.h>
#include "web.h"


class HttpServer {
    public:
        HttpServer();
        void start();

    private:
        std::string serverName;
        unsigned int serverPort;
        // LogManager logManager;
        void testDatabaseConnection();
};

#endif