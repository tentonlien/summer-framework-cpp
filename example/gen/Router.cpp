#include "MainController.cpp"

#include <iostream>
#include <string>

#include "json.h"

#include "../src/cpp/entity/UserEntity.cpp"

void router(HttpRequest* request, HttpResponse* response) {
    std::string accessControlAllowOrigin = "Access-Control-Allow-Origin: *\r\n";
    std::string accessControlAllowMethod = "Access-Control-Allow-Methods: GET\r\n";
    std::string returnData;

    MainController mainController;

    mainController.setRequest(request);
    mainController.setResponse(response);

    if (request -> uri == "/info") {
        returnData = mainController.getInfo();
    } 
    else if (request -> uri == "/login") {
        returnData = mainController.getUser2();
    } 
    else if (request -> uri == "/time") {
        returnData = mainController.getTime();
    } 
else if (request -> uri == "/user") {
        UserEntity userEntity = mainController.getUser();
        JsonParser jsonParser;
            jsonParser.createKey("name", userEntity.getName());
    jsonParser.createKey("password", userEntity.getPassword());

        // jsonParser.createKey("key-name", object-name-6.function-name-3());
        returnData = jsonParser.toString();
        
    } 
 else {
        returnData = "<body style=\"margin:0;\"><div style=\"background: #10a9f5;color:white;font-family: Arial;padding: 20px;padding-left:10px;font-size:20px;\">Summer Framework App</div><p style=\"margin-left: 20px;font-family:Arial;\"><span style=\"color:red;\">Error</span>: URL <code style=\"background:#e5e5e5;font-size:16px;padding:5px;border-radius:2px;\">" + request -> uri + "</code> Not Found.</p></body>";
    }
    response -> setData(returnData);
}