/* Created by Tenton Lien on 4/6/2019 */

#include "router.h"
#include <iostream>
#include <string>

void router(HttpRequest* request, HttpResponse* response) {
    std::string accessControlAllowOrigin = "Access-Control-Allow-Origin: *\r\n";
    std::string accessControlAllowMethod = "Access-Control-Allow-Methods: GET\r\n";
    std::string returnData;

    if (request -> uri == "/info") {
        returnData = _info(request, response);
    } else if (request -> uri == "/user") {
        returnData = _user(request, response);
    } else if (request -> uri == "/time") {
        returnData = _time(request, response);
    } else {
        returnData = "<body style=\"margin:0;\"><div style=\"background: #10a9f5;color:white;font-family: Arial;padding: 20px;padding-left:10px;font-size:20px;\">Summer Framework App</div><p style=\"margin-left: 20px;font-family:Arial;\"><span style=\"color:red;\">Error</span>: URL <code style=\"background:#e5e5e5;font-size:16px;padding:5px;border-radius:2px;\">" + request -> uri + "</code> Not Found.</p></body>";
    }
    response -> setData(returnData);
}