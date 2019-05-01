/* Created by Tenton Lien on 4/16/2019 */

#include <iostream>
#include <sstream>
#include <string>

#include "web.h"

HttpResponse::HttpResponse() {
    this -> status = HttpResponseStatus.OK_200;
    this -> contentType = HttpContentType.HTML;
    this -> data = "";
}


std::string HttpResponse::generate() {
    std::string responseString = "HTTP/1.1 ";
    responseString += this -> status + "\r\n";
    responseString += "Content-Type: " + this -> contentType + "\r\n";
    responseString += "Content-Length: " + std::to_string(data.length()) + "\r\n";
    responseString += "\r\n";

    responseString += data;
    responseString += "\r\n\r\n";

    return responseString;
}


void HttpResponse::setData(std::string data) {
    this -> data = data;
}