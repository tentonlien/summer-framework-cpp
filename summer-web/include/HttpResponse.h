/* Created by Tenton Lien on 1/7/2020 */

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <exception>
#include <functional>
#include <queue>
#include <string>
#include <thread>
#include <vector>

// HttpResponse
class {
    public:
        std::string OK_200 = "200 OK";
        std::string FORBIDDEN_403 = "403 Forbidden";
        std::string NOT_FOUND_404 = "404 Not Found";
        std::string INTERNAL_SERVER_ERROR_500 = "500 Internal Server Error";
} HttpResponseStatus;


class HttpResponse {
    public:
        HttpResponse();
        std::string getResponseBody();
        void setResponseBody(std::string);
        std::string generate();
        void setCookie(std::string);

    private:
        std::string status;
        std::string contentType;
        std::string responseBody;
        std::string setCookieStr;
};

#endif