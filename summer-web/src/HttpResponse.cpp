/* Created by Tenton Lien on 4/16/2019 */

#include <iostream>
#include <sstream>
#include <string>

#include "HttpRequest.h"
#include "HttpResponse.h"

HttpResponse::HttpResponse() {
    this -> status = HttpResponseStatus.OK_200;
    this -> contentType = HttpContentType.HTML;
    this -> responseBody = "";
    this -> setCookieStr = "";
}


std::string HttpResponse::generate() {
    std::string responseString = "HTTP/1.1 ";
    responseString += this -> status + "\r\n";
    responseString += "Content-Type: " + this -> contentType + "\r\n";
    responseString += "Content-Length: " + std::to_string(this -> responseBody.length()) + "\r\n";
    responseString += this -> setCookieStr;
    responseString += "\r\n";

    responseString += this -> responseBody;
    responseString += "\r\n\r\n";

    return responseString;
}


std::string HttpResponse::getResponseBody() {
    return this -> responseBody;
}


void HttpResponse::setResponseBody(std::string body) {
    this -> responseBody = body;
}


void HttpResponse::setCookie(std::string setCookieStr) {
    this -> setCookieStr += "Set-Cookie: " + setCookieStr + "\r\n";
}