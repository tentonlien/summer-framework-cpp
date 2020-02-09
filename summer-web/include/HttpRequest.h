/* Created by Tenton Lien on 1/7/2020 */

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <exception>
#include <functional>
#include <queue>
#include <string>
#include <thread>
#include <vector>

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

#endif