/* Created by Tenton Lien on 4/6/2019 */

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "HttpRequest.h"

HttpRequest::HttpRequest(std::string raw) {
    this -> raw = raw;
    parseHeader();
    if (this -> method != HttpRequestMethod.GET) {
        parseBody(this -> getContentLength());
    }
}


int HttpRequest::getContentLength() {
    unsigned int pos = this -> raw.find("Content-Length");
    if (pos == std::string::npos) {
        pos = this -> raw.find("content-length");
        if (pos == std::string::npos) {
            return 0;
        }
    }

    unsigned int pos2 = this -> raw.find("\r\n", pos + 16);
    if (pos2 != std::string::npos) {
        std::string::size_type sz;
        std::string temp;
        try {
            temp = this -> raw.substr(pos + 16, pos2 - pos - 16);
            return stoi(temp, &sz);
        } catch(std::exception& e) {
            std::cout << e.what() << ": '" << 
                        temp <<
                        "' is not a valid content type." << std::endl;
            return 0;
        }
    }
    return 0;
}


void HttpRequest::parseHeader() {
    std::istringstream iss (this -> raw);
    std::string temp;
    std::getline(iss, temp);
    std::stringstream ss(temp);
    ss >> this -> method >> this -> uri;
}


void HttpRequest::parseBody(int length) {
    int pos = this -> raw.find("\r\n\r\n") + 4;
    try {
        this -> body = raw.substr(pos, length);
    } catch(std::exception &e) {
        std::cout << "Exception during parsing request body: " << e.what() << std::endl;
    }
    
}