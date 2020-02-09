/* Created by Tenton Lien on 4/16/2019 */

#include "Controller.h"

void Controller::setRequest(HttpRequest* request) {
    this -> request = request;
}

void Controller::setResponse(HttpResponse* response) {
    this -> response = response;
}