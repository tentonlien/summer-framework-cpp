/* This file will be auto updated by summer-cli */

#include "router.h"
#include <iostream>
#include "methods.h"
#include <string>

std::string router(Method method, std::string url) {
    std::string status = "HTTP/1.1 200 OK\r\n";
    std::string contentType = "Content-Type: text/html\r\n";
    std::string contentLength = "Content-Length: ";
    std::string accessControlAllowOrigin = "Access-Control-Allow-Origin: *\r\n";
    std::string accessControlAllowMethod = "Access-Control-Allow-Methods: GET\r\n";
    std::string returnData = "";

    if (url == "/info") {
        returnData = _info(method, "data");
    } else if (url == "/user") {
        returnData = _user(method, "data");
    } else if (url == "/time") {
        returnData = _time(method, "data");
    } else {
        status = "HTTP/1.1 404 Internal Server Error\r\n";
        returnData = "<body style=\"margin:0;\"><div style=\"background: #10a9f5;color:white;font-family: Arial;padding: 20px;padding-left:10px;font-size:20px;\">Summer Framework App</div><p style=\"margin-left: 20px;font-family:Arial;\"><span style=\"color:red;\">Error</span>: URL <code style=\"background:#e5e5e5;font-size:16px;padding:5px;border-radius:2px;\">" + url + "</code> Not Found.</p></body>";
    }
    
    contentLength += std::to_string(returnData.length()) + "\r\n";
    std::string response = status + contentType + contentLength + accessControlAllowOrigin + accessControlAllowMethod + "\r\n" + returnData + "\r\n\r\n";

    return response;
}