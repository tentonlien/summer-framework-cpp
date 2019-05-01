/* Created by Tenton Lien on 4/6/2019 */

#include "MainController.cpp"
#include <iostream>
#include <string>

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

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
    } else if (request -> uri == "/user") {
        UserEntity user = mainController.getUser();
        std::string userName = user.getName();
        std::string userPassword = user.getPassword();

        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

        rapidjson::Value value(rapidjson::kStringType);
        value = rapidjson::StringRef(userName.c_str());
        document.AddMember("name", value, allocator);
        value.SetString(rapidjson::StringRef(userPassword.c_str()));
        document.AddMember("password", value, allocator);
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        returnData = buffer.GetString();
        
    } else if (request -> uri == "/user2") {
        returnData = mainController.getUser2();
    } else if (request -> uri == "/time") {
        returnData = mainController.getTime();
    } else {
        returnData = "<body style=\"margin:0;\"><div style=\"background: #10a9f5;color:white;font-family: Arial;padding: 20px;padding-left:10px;font-size:20px;\">Summer Framework App</div><p style=\"margin-left: 20px;font-family:Arial;\"><span style=\"color:red;\">Error</span>: URL <code style=\"background:#e5e5e5;font-size:16px;padding:5px;border-radius:2px;\">" + request -> uri + "</code> Not Found.</p></body>";
    }
    response -> setData(returnData);
}