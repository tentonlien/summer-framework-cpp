/* Created by Tenton Lien on 4/6/2019 */

#ifndef SUMMER_WEB_H
#define SUMMER_WEB_H

#include <exception>
#include <string>


// HttpRequest
class {
    public:
        std::string GET = "GET";
        std::string POST = "POST";
        std::string PUT = "PUT";
        std::string DELETE = "DELETE";
        // GET, POST, PUT, PATCH, DELETE, COPY, HEAD, OPTIONS, PURGE, LOCK, UNLOCK, PROPFIND, VIEW
} HttpRequestMethod;


class {
    public:
        std::string JSON = "application/json";
        std::string HTML = "text/html";
        std::string TEXT = "text/plain";
} HttpContentType;


class HttpRequest {
    public:
        std::string method;
        std::string uri;
        std::string body;
        std::string host;
        std::string cookie;
        std::string userAgent;
        std::string accept;
        std::string acceptLanguage;
        std::string acceptEncoding;
        std::string connection;

        HttpRequest(std::string);
        std::string getContentType();
        int getContentLength();
        bool isAjaxRequest();

    private:
        std::string raw;

        void parseHeader();
        void parseBody(int);
};


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
        void setData(std::string);
        std::string generate();

    private:
        std::string status;
        std::string contentType;
        std::string data;
};


//LogManager
class LogManager {
    public:
        void setServerName(std::string);
        void addInfo(std::string);
        void addWarning(std::string);
        void addError(std::string);
        void addFatalError(std::string);

    private:
        std::string serverName;

        std::string getCurrentTime();
};


// HttpServer
class HttpServer {
    public:
        HttpServer(std::string, unsigned int port);
        void start();

    private:
        std::string serverName;
        unsigned int serverPort;
        LogManager logManager;
        void testDatabaseConnection();
};


// Controller
class Controller
{
  protected:
    HttpRequest* request;
    HttpResponse* response;
};

#endif