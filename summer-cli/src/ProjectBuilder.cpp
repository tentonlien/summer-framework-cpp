/* Created by Tenton Lien on 12/14/2019 */

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "ProjectBuilder.h"
#include "SummerCLI.h"
#include "TemplateProcessor.h"
#include "FileScanner.h"
#include "AnnotationParser/RestControllerAnnotationParser.hpp"
#include "ProjectObjectModel.h"

#include <nlohmann-json/json.hpp>

using json = nlohmann::json;


class EntityClass {
  public:
    std::string name;
    std::vector<std::string> vars;
};


ProjectBuilder::ProjectBuilder() {
    FileScanner fileScanner;
    // exit(0);
    this -> projectObjectModel = new ProjectObjectModel;
    generateApplicationProperties();
    generateBanner();
    generateRouter();
    if (system("make") == -1) {
        std::cerr << "Build failed" << std::endl;
    }
}

ProjectBuilder::~ProjectBuilder() {
    delete this -> projectObjectModel;
}


// Read data from src/resources/application.properties
void ProjectBuilder::generateApplicationProperties() {
    std::map<std::string, std::string> applicationProperties;

    try {
        std::string applicationPropertiesText = File::readTextFile("src/resources/application.properties");

        // Divide into lines and store in vectors
        std::vector<std::string> applicationPropertiesVector;
    
        std::regex reg("([\r\n]{2}|[\r\n]{1})|$");
        std::smatch result;

        while (std::regex_search(applicationPropertiesText, result, reg)) {
            std::string temp = result.prefix().str();
            std::regex regEmpty("[\\s]*");
            if (!std::regex_match(temp, regEmpty)) {
                applicationPropertiesVector.push_back(result.prefix().str());
            }

            applicationPropertiesText = result.suffix().str();

            if (applicationPropertiesText.length() == 0) {
                break;
            }
        }

        // Analysing keys and values
        for (auto item: applicationPropertiesVector) {
            std::regex regProperty(".*[=].*");
            if (std::regex_match(item, regProperty)) {
                std::string key = "";
                std::string value = "";
                unsigned int i = 0;

                // Read key
                while (item[i] != '=') {
                    if (isalnum(item[i]) || item[i] == '.') {
                        key += item[i];
                    }

                    if (i != item.length() - 1) {
                        i ++;
                    } else {
                        // Handle with error
                    }
                }

                i ++;

                // Read value
                while (i < item.length()) {
                    if (item[i] != ' ') {
                        value += item[i];
                    }

                    i ++;
                }

                applicationProperties.insert({key, value});
            }
        }

        TemplateProcessor templateProcessor(programDirectory + "/template/ApplicationProperties.cpp");
        templateProcessor.insertElement("applicationName", this -> projectObjectModel -> projectName);

        auto iterator = applicationProperties.begin();
        while (iterator != applicationProperties.end()) {
            templateProcessor.insertRepeatedElement("0", "data-key", iterator -> first);
            templateProcessor.insertElement("data-value", iterator -> second);
            iterator ++;
        }
        templateProcessor.output("gen/ApplicationProperties.cpp");
    } catch(IOException& e) {
        std::cerr << "Generate application.properties failed";
    }
}


// Generate banner text
void ProjectBuilder::generateBanner() {
    try {
        TemplateProcessor templateProcessor(programDirectory + "/template/BannerText.cpp");
    
        // Generate banner
        std::string bannerText = File::readTextFile("src/resources/banner.txt");
        std::vector<std::string> bannerTextVector;
        std::string::size_type pos = bannerText.find("\\");
        while (pos != std::string::npos) {
            bannerText.replace(pos, 1 , "\\\\");
            pos = bannerText.find("\\", pos + 2);
        }

        std::regex reg("([\r\n]{2}|[\r\n]{1})|$");
        std::smatch result;

        while (std::regex_search(bannerText, result, reg)) {
            std::string temp = result.prefix().str();
            std::regex regEmpty("[\\s]*");
            if (!std::regex_match(temp, regEmpty)) {
                bannerTextVector.push_back(result.prefix().str());
            }

            bannerText = result.suffix().str();

            if (bannerText.length() == 0) {
                break;
            }
        }

        bannerText = "";

        for (auto item: bannerTextVector) {
            bannerText += item + "\\n";
        }
        templateProcessor.insertElement("bannerText", bannerText);

        templateProcessor.output("gen/BannerText.cpp");
    } catch(IOException& e) {
        std::cerr << "Generate BannerText.cpp failed";
    }
}

// Read data from router
bool ProjectBuilder::generateRouter() {
    // Parsing entity annotations
    std::string entityDir = "src/cpp/model/";
    std::vector<EntityClass> entityClasses;
    std::vector<FileItem> fileItems = File::getFiles(entityDir);
    for (size_t i = 0; i < fileItems.size(); i ++) {
        EntityClass entityClass;
        std::string entityClassString = File::readTextFile(entityDir + fileItems[i].fileName);
        size_t pos = entityClassString.find("class ");
        if (pos != std::string::npos) {
            pos += 6;
            size_t pos2 = pos;
            while (entityClassString[pos2] != ' ' &&
                    entityClassString[pos2] != '{' &&
                    entityClassString[pos2] != ':' &&
                    pos2 < entityClassString.length()) {
                pos2 ++;
            }
            entityClass.name = entityClassString.substr(pos, pos2 - pos);
        }
        // std::cout << "Class Name: " << entityClass.name << std::endl;

        std::regex memberVariableRE("((string)|(std::string))[\\s]+[[:alnum:]]+[\\s]*;");
        std::regex memberMethodRE("((void)|(string))[\\s]+[[:alnum:]]+[\\s]*[\\(].*[\\)]");
        std::smatch result;
        std::string temp = entityClassString;

        while (std::regex_search(temp, result, memberVariableRE)) {
            // std::cout << "Search member variable: " << result.str() << std::endl;
            std::smatch result2;
            std::string temp2 = result.str();
            if (std::regex_search(temp2, result2, std::regex("[A-Za-z0-9:_]+"))) {
                temp2 = result2.suffix().str();
                if (std::regex_search(temp2, result2, std::regex("[A-Za-z0-9:_]+"))) {
                    entityClass.vars.push_back(result2.str());
                }
            }
            temp = result.prefix().str() + result.suffix().str();
        }

        while (std::regex_search(temp, result, memberMethodRE)) {
            // std::cout << "Search member method: " << result.str() << std::endl;
            temp = result.prefix().str() + result.suffix().str();
        }
        entityClasses.push_back(entityClass);
    }

    // Parsing controller annotations
    std::string controllerDir = "src/cpp/controller/";
    std::vector<RestController> restControllers;
    fileItems = File::getFiles(controllerDir);
    TemplateProcessor routerTemplateHandler(programDirectory + "/template/Router.cpp");

    for (size_t i = 0; i < fileItems.size(); i ++) {
        routerTemplateHandler.insertRepeatedElement("0", "cpp-source", "../" + controllerDir + fileItems[i].fileName);
        
        RestControllerAnnotationParser restControllerAnnotationParser;
        restControllerAnnotationParser.scanAnnotations(controllerDir + fileItems[i].fileName);
        restControllerAnnotationParser.parse();
        restControllerAnnotationParser.print();

        RestController* rcp = &(restControllerAnnotationParser.restController);
        routerTemplateHandler.insertRepeatedElement("1", "class-name", rcp -> name);
        std::string objectName = rcp -> name;
        if (objectName[0] > 'Z') {
            objectName[0] = toupper(objectName[0]);
        } else {
            objectName[0] = tolower(objectName[0]);
        }
        routerTemplateHandler.insertElement("object-name", objectName);
        routerTemplateHandler.insertElement("object-name-2", objectName);
        routerTemplateHandler.insertElement("object-name-3", objectName);
        routerTemplateHandler.insertElement("object-name-4", objectName);
        routerTemplateHandler.insertElement("object-name-5", objectName);
        routerTemplateHandler.insertElement("object-name-6", objectName);

        for (size_t k = 0; k < restControllerAnnotationParser.restController.requestMappings.size(); k ++) {
            RequestMapping* rmp = &(restControllerAnnotationParser.restController.requestMappings[k]);
            if (rmp -> returnType == "string" || rmp -> returnType == "std::string") {
                routerTemplateHandler.insertRepeatedElement("2", "uri", rmp -> value);
                routerTemplateHandler.insertElement("object-name-4", objectName);
                routerTemplateHandler.insertElement("function-name", rmp -> functionName);
            } /* else if (rmp -> returnType == "RestResponse") {
                routerTemplateHandler.insertRepeatedElement("3", "uri-2", rmp -> value);
                routerTemplateHandler.insertElement("object-name-4", objectName);
                routerTemplateHandler.insertElement("function-name-2", rmp -> functionName);
            } */ else {
                routerTemplateHandler.insertRepeatedElement("4", "uri-3", rmp -> value);
                routerTemplateHandler.insertElement("object-name-5", objectName);
                routerTemplateHandler.insertElement("function-name-3", rmp -> functionName);
            }
        }
    }

    std::string* routerTemplateContent = routerTemplateHandler.getTemplateContentPointer();
    size_t pos = routerTemplateContent -> find("else");
    *routerTemplateContent = routerTemplateContent -> substr(0, pos) + routerTemplateContent -> substr(pos + 5, routerTemplateContent -> length() - pos - 5); 
    routerTemplateHandler.output("gen/Router.cpp");
    // routerTemplateHandler.print();
    return true;
}