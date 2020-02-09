{{repeat-start id=0}}#include "{{cpp-source}}"{{repeat-end}}
#include <iostream>
#include <string>
#include <org/summerframework/web.h>

//#include "json.hpp"
//using json = nlohmann::json;

//#include "../src/cpp/entity/UserEntity.cpp"
//asdfasdfasdf

void router(HttpRequest* request, HttpResponse* response) {
    std::string accessControlAllowOrigin = "Access-Control-Allow-Origin: *\r\n";
    std::string accessControlAllowMethod = "Access-Control-Allow-Methods: GET\r\n";
    std::string returnData;

{{repeat-start id=1}}    {{class-name}} {{object-name}};{{repeat-end}}
    {{object-name-2}}.setRequest(request);
    {{object-name-3}}.setResponse(response);

    if (false) {}
{{repeat-start id=2}}   else if (request -> uri == "{{uri}}") {
        returnData = {{object-name-4}}.{{function-name}}();
    } {{repeat-end}}{{repeat-start id=3}}   else if (request -> uri == "{{uri-2}}") {
        RestResponse* restResponse = {{object-name-5}}.{{function-name-2}}();
        returnData = restResponse -> toString();
        delete restResponse;
    } {{repeat-end}}{{repeat-start id=4}}    else if (request -> uri == "{{uri-3}}") {
        returnData = {{object-name-6}}.{{function-name-3}}().serialize();
        // jsonParser.createKey("key-name", object-name-6.function-name-3());
        
    } {{repeat-end}} else {
        returnData = "<body style=\"margin:0;\"><div style=\"background: #10a9f5;color:white;font-family: Arial;padding: 20px;padding-left:10px;font-size:20px;\">Summer Framework App</div><p style=\"margin-left: 20px;font-family:Arial;\"><span style=\"color:red;\">Error</span>: URL <code style=\"background:#e5e5e5;font-size:16px;padding:5px;border-radius:2px;\">" + request -> uri + "</code> Not Found.</p></body>";
    }
    response -> setResponseBody(returnData);
}