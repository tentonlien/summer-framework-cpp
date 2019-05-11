/* Created by Tenton Lien on 4/11/2019 */

#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <unistd.h>
#include <vector>

#include "AnnotationParser/RestControllerAnnotationParser.hpp"
#include "TemplateHandler.hpp"

#include "tinyxml2.h"

#include "summer.h"

const std::string cliVersion = "0.1";

std::string programDirectory;
std::string appName = "";

class Dependency {
  public:
    std::string name;
    std::string path;
};

std::vector<Dependency> dependencies;
std::map<std::string,std::string> applicationProperties;


// Read POM file
int readPOM() {
    tinyxml2::XMLDocument doc;

    if (doc.LoadFile("pom.xml")) {
        std::cerr << "ERROR: " << doc.ErrorStr() << std::endl;
        return -1;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement();
    if (root == NULL) {
        // printLog(Logs.ERROR, "Failed to load file: No root element");
        doc.Clear();
        return -1;
    }

    for (tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "name") {
            appName = elem -> FirstChild() -> ToText() -> Value();
        } else if (elemName == "dependencies") {
            Dependency tempDependency;
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "dependency") {
                    
                    for (tinyxml2::XMLElement* subSubElem = subElem -> FirstChildElement(); subSubElem != NULL; subSubElem = subSubElem -> NextSiblingElement()) {
                        std::string subSubElemName = subSubElem->Value();
                        if (subSubElemName == "groupId") {
                            tempDependency.path = subSubElem -> FirstChild() -> ToText() -> Value();
                            tempDependency.path += "/";
                            for (unsigned int i = 0; i < tempDependency.path.length(); i ++) {
                                if (tempDependency.path[i] == '.') {
                                    tempDependency.path[i] = '/';
                                }
                            }
                        } else if (subSubElemName == "artifactId") {
                            tempDependency.name = subSubElem -> FirstChild() -> ToText() -> Value();
                            tempDependency.path += subSubElem -> FirstChild() -> ToText() -> Value();
                            tempDependency.path += "/";
                        } else if (subSubElemName == "version") {
                            tempDependency.path += subSubElem -> FirstChild() -> ToText() -> Value();
                        }
                    }
                }
                dependencies.push_back(tempDependency);
            }
        }
    }
    doc.Clear();
    return 0;
}


void analyzeDependencies(std::string* buildCommand) {
    for (unsigned int i = 0; i < dependencies.size(); i ++) {
        *buildCommand += "-I" + programDirectory + "/repository/" + dependencies[i].path + "/include ";

        // Detect shared libraries
        std::vector<std::string> files = getFiles(programDirectory + "/repository/" + dependencies[i].path + "/lib");
        if (!files.empty()) {
            *buildCommand += "-L" + programDirectory + "/repository/" + dependencies[i].path + "/lib ";
            for (unsigned int k = 0; k < files.size(); k ++) {
                // std::cout << files.at(i) << std::endl;
                std::regex libraryFileNameRegularExpression("lib.*\\.so");
                std::regex libraryFileNameWithVersionRegularExpression("lib.*\\.so\\..*");
                if (std::regex_match(files[k], libraryFileNameRegularExpression)) {
                    *buildCommand += "-l" + files.at(k).substr(3, files[k].length() - 6) + " ";
                } else if (std::regex_match(files[k], libraryFileNameWithVersionRegularExpression)) {
                    *buildCommand += programDirectory + "/repository/" + dependencies[i].path + "/lib/" + files.at(k) + " ";
                }
                
            }

        }

        if (dependencies[i].name == "summer-web") {
            *buildCommand += "-I ../src/cpp/controller ";
            *buildCommand += "../src/cpp/controller/*.cpp ";
            *buildCommand += "../src/cpp/service/*.cpp ";
            *buildCommand += "../src/cpp/dao/*.cpp ";
        }
    }
}


// Read data from src/resources/application.properties
void readApplicationProperties() {
    std::string applicationPropertiesText;

    if (!readTextFile("src/resources/application.properties", &applicationPropertiesText)) {
        std::cerr << "Error: fail to open \"application.properties\"" << std::endl;
        exit(0);
    }

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

            // Read key
            while (i < item.length()) {
                if (item[i] != ' ') {
                    value += item[i];
                }

                i ++;
            }

            applicationProperties.insert({key, value});
        }
    }
}


void readBanner() {
    std::string bannerText;
    readTextFile("src/resources/banner.txt", &bannerText);  // TO-DO: Handle with error
    std::vector<std::string> bannerTextVector;

    std::string::size_type pos = bannerText.find("\\");
    while (pos != std::string::npos) {
        bannerText.replace(pos, 1 , "\\\\");
        pos = bannerText.find("\\", pos + 3);
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

    TemplateHandler templateHandler(programDirectory + "/template/BannerText.cpp");
    templateHandler.insertElement("banner-text", bannerText);
    templateHandler.output("gen/BannerText.cpp");
}


void doCreate(std::string projectName) {
    char userResponse;
    std::cout << "Are you going to build a Summer Web project? [Y/N]";
    std::cin >> userResponse;
    if (toupper(userResponse) == 'Y') {
        std::cout << "Creating..." << std::endl << std::endl;
        std::cout << "For web development, some required modules listed below have been auto imported." << std::endl;
        std::cout << "org.summerframework.summer-web.1.0" << std::endl;
        std::cout << "org.summerframework.summer-json-wrapper.1.0" << std::endl;
        std::cout << "org.summerframework.summer-data-sql.1.0" << std::endl << std::endl;;

        std::cout << "Complete. " << std::endl;
    } else {
        std::cout << "This part is still in test phase." << std::endl;
    }
}


void doBuild() {
    // Initial configuration
    readPOM();
    readApplicationProperties();

    std::string buildCommand = "cd ./out && g++ ../src/cpp/*.cpp ../gen/*.cpp -I ../src/cpp ";
    analyzeDependencies(&buildCommand);

    // Generate applicationProperties.cpp
    TemplateHandler templateHandler(programDirectory + "/template/ApplicationProperties.cpp");
    templateHandler.insertElement("data-appname", appName);

    auto itetator = applicationProperties.begin();
    while (itetator != applicationProperties.end()) {
        templateHandler.insertRepeatedElement("0", "data-key", itetator -> first);
        templateHandler.insertElement("data-value", itetator -> second);
        itetator ++;
    }
    templateHandler.output("gen/ApplicationProperties.cpp");

    // Generate Banner.cpp
    readBanner();

    // Generate router.cpp by parsing annotations in controller source
    std::string dir = "src/cpp/controller/";
    std::vector<RestController> restControllers;
    std::vector<std::string> fileList = getFiles(dir);
    TemplateHandler routerTemplateHandler(programDirectory + "/template/Router.cpp");

    for (size_t i = 0; i < fileList.size(); i ++) {
        // std::cout << fileList[i] << std::endl;
        routerTemplateHandler.insertRepeatedElement("0", "cpp-source", fileList[i]);
        
        RestControllerAnnotationParser restControllerAnnotationParser;
        restControllerAnnotationParser.scanAnnotations(dir + fileList[i]);
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
        routerTemplateHandler.insertElement("object-name-2", objectName);

        for (size_t k = 0; k < restControllerAnnotationParser.restController.requestMappings.size(); k ++) {
            RequestMapping* rmp = &(restControllerAnnotationParser.restController.requestMappings[k]);
            if (rmp -> returnType == "string" || rmp -> returnType == "std::string") {
                routerTemplateHandler.insertRepeatedElement("2", "uri", rmp -> value);
                routerTemplateHandler.insertElement("object-name-3", objectName);
                routerTemplateHandler.insertElement("function-name", rmp -> functionName);
            } else {
                std::cout << "Unsuppoted return type: " << rmp -> returnType << std::endl;
            }
        }
        // restControllers.push_back(restControllerAnnotationParser.restController);
    }

    std::string* routerTemplateContent = routerTemplateHandler.getTemplateContentPointer();
    size_t pos = routerTemplateContent -> find("else");
    *routerTemplateContent = routerTemplateContent -> substr(0, pos) + routerTemplateContent -> substr(pos + 5, routerTemplateContent -> length() - pos - 5); 
    routerTemplateHandler.output("gen/Router.cpp");
    // templateHandler.insertElement("data-appname", appName);
    
    
    // Define application name
    if (appName == "") {
        buildCommand += "-o Application ";
    } else {
        buildCommand += "-o " + appName + " ";
    }

    buildCommand += "-Wl,-rpath ./lib ";
        
    // Build project
    int status = system(buildCommand.c_str());
    if (status == -1) {
        std::cout << "Error: g++ compiler not found" << std::endl;
    } else if (status == 256) {
        std::cout << "Error: Build failed" << std::endl;
        std::cout << buildCommand << std::endl;
    } else {
        std::cout << "Build complete" << std::endl;
    }
}


void doRun() {
    readPOM();
    std::string targetUri = "cd ./out && ./";
    int status = system((targetUri + appName).c_str());
    if (status == 256) {
        std::cout << "Error: Failed to run the target program" << std::endl;
    }
}


void doList(std::string arg) {
    if (arg == "properties") {
        if (applicationProperties.empty()) {
            readApplicationProperties();
        }
        auto itetator = applicationProperties.begin();
        while (itetator != applicationProperties.end()) {
            std::cout << "Key = \"" << itetator -> first << "\", Value = \"" << itetator -> second << "\"" << std::endl;
            itetator ++;
        }
    } else if (arg == "dependencies") {
        readPOM();
        for (auto item: dependencies) {
            std::cout << item.name << std::endl;
        }
    } else {
        std::cout << "Unsupported argument \"" << arg << "\"" << std::endl;
    }
}


int main(int argc, char* argv[]) {

    // Get the location where the cli-tool exists
    char buffer[1024];
    ssize_t status = readlink("/proc/self/exe", buffer, 1024);
    if (status == -1) {
        std::cout << "Error: cannot get the location where the cli-tool exists" << std::endl;
    }

    programDirectory = buffer;
    programDirectory = programDirectory.substr(0, programDirectory.length() - strlen(argv[0]) - 1);

    // Handle with opereation command
    if (argc < 2) {
        return 0;
    } else if (strcmp(argv[1], "create") == 0) {
        if (argc < 3) {
            std::cout << "summer: \033[40;1;31merror\033[0m: project name required" << std::endl << std::endl;
            std::cout << "To create a new Summer project, use \"summer create <project-name>\"." << std::endl;
        } else {
            doCreate(argv[2]);
        }
        
    } else if (strcmp(argv[1], "build") == 0) {
        doBuild();
    } else if (strcmp(argv[1], "run") == 0) {
        doRun();
    } else if (strcmp(argv[1], "list") == 0) {
        if (argc == 3) {
            doList(argv[2]);
        }
    } else if (strcmp(argv[1], "version") == 0) {
        std::cout << "Version: " << cliVersion << std::endl;
    }
    return 0;
}