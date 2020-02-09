/* Created by Tenton Lien on 1/7/2020 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <exception>
#include <functional>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "HttpRequest.h"
#include "HttpResponse.h"

// Controller
class Controller
{
  public:
    void setRequest(HttpRequest*);
    void setResponse(HttpResponse*);
  protected:
    HttpRequest* request;
    HttpResponse* response;
};

#endif