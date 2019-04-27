/* Created by Tenton Lien on 4/11/2019 */

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>
#include <unistd.h>
#include "tinyxml2.h"

const std::string cliVersion = "1.0";

std::string programDirectory;
std::string appName = "";

std::vector<std::string> dependencies;
std::map<std::string,std::string> applicationProperties;

std::string readTextFile(std::string path) {
    std::ifstream textFile(path);

    if (!textFile) {
        // showError(0, 0, "Loading Error", "Failed to read file");
        std::cerr << "Failed to read file: " << path << std::endl;
    }

    std::istreambuf_iterator<char> begin(textFile);
    std::istreambuf_iterator<char> end;
    std::string fileContent(begin, end);
    textFile.close();
    return fileContent;
}


int writeTextFile(std::string path, std::string data) {
    std::ofstream textFile(path);
    if (!textFile) {
        std::cerr << "Failed to open file while writing" << std::endl;
        return -1;
    }
    textFile << data;
    textFile.close();
    return 0;
}


int insertElementIntoTemplate(std::string* cppTemplate, std::string tag, std::string value) {
    tag = "{{" + tag + "}}";
    int pos = cppTemplate -> find(tag);
    if (pos != std::string::npos) {
        // std::cout << "pos " << pos << std::endl;
        cppTemplate -> replace(pos, tag.length(), value);
        //std::cout << "$" << value << "$" << std::endl;
    } else {
        std::cout << "Tag not found" << std::endl;
        return -1;
    }
    return 0;
}


int repeatElement(std::string* cppTemplate, std::string tagId) {
    std::regex regRepeatedElement("\\{\\{repeat-start id=" + tagId + "\\}\\}.*\\{\\{repeat-end\\}\\}");
    std::smatch result;
    if (std::regex_search(*cppTemplate, result, regRepeatedElement)) {
        // std::cout << result.str() << std::endl;
        std::string temp = result.str();
        insertElementIntoTemplate(&temp, "repeat-start id=" + tagId, "");
        insertElementIntoTemplate(&temp, "repeat-end", "");
        *cppTemplate = result.prefix().str() + temp + "\n" + result.str() + result.suffix().str();
    }
    return 0;
}


int removeRepeatTag(std::string* cppTemplate, std::string tagId) {
    std::regex regRepeatedElement("\\{\\{repeat-start id=" + tagId + "\\}\\}.*\\{\\{repeat-end\\}\\}");
    std::smatch result;
    if (std::regex_search(*cppTemplate, result, regRepeatedElement)) {
        // std::cout << result.str() << std::endl;
        // std::string temp = result.str();
        // insertElementIntoTemplate(&temp, "{{repeat-start id=" + tagId + "}}", "");
        // insertElementIntoTemplate(&temp, "{{repeat-end}}", "");
        *cppTemplate = result.prefix().str() + result.suffix().str();
    }
    return 0;
}


// Read POM file
int readPOM() {
    tinyxml2::XMLDocument doc;

    if(doc.LoadFile("pom.xml")) {
        std::cerr << "ERROR: " << doc.ErrorStr() << std::endl;
        return -1;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement();
    if(root == NULL) {
        // printLog(Logs.ERROR, "Failed to load file: No root element");
        doc.Clear();
        return -1;
    }

    for (tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "name") {
            appName = elem -> FirstChild() -> ToText() -> Value();
        } else if (elemName == "web") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "port") {
                    // param_web_port = subElem -> FirstChild() -> ToText() -> Value();
                }
            }
        } else if (elemName == "dependencies") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "dependency") {
                    dependencies.push_back(subElem -> FirstChild() -> ToText() -> Value());
                }
            }
        }
    }
    doc.Clear();
    return 0;
}


void analyzeDependencies(std::string* buildCommand) {
    for (unsigned int i = 0; i < dependencies.size(); i ++) {
        if (dependencies[i] == "summer-core") {
            *buildCommand += "-I" + programDirectory + "/repository/org/summerframework/summer-core " + programDirectory + "/repository/org/summerframework/summer-core/*.cpp ";
        } else if (dependencies[i] == "summer-web") {
            *buildCommand += "-I" + programDirectory + "/repository/org/summerframework/summer-web " + programDirectory + "/repository/org/summerframework/summer-web/*.cpp ";
            *buildCommand += "src/cpp/controller/*.cpp ";
            *buildCommand += "src/cpp/service/*.cpp ";
            *buildCommand += "src/cpp/dao/*.cpp ";
        } else if (dependencies[i] == "summer-sql") {
            *buildCommand += "-I" + programDirectory + "/repository/org/summerframework/summer-sql " + programDirectory + "/repository/org/summerframework/summer-sql/*.cpp ";
            *buildCommand += "$(mysql_config --cflags) $(mysql_config --libs) ";
        }
    }
}


// Read data from src/resources/application.properties
void readApplicationProperties() {
    std::string applicationPropertiesText = readTextFile("src/resources/application.properties");
    // std::cout << applicationPropertiesText << std::endl;
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
    std::string bannerText = readTextFile("src/resources/banner.txt");
    std::string bannerTemplate = readTextFile(programDirectory + "/templates/banner.cpp");
    std::vector<std::string> bannerTextVector;

    int pos = bannerText.find("\\");
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

    insertElementIntoTemplate(&bannerTemplate, "banner-text", bannerText);
    // std::cout << bannerTemplate << std::endl;
    writeTextFile("target/banner.cpp", bannerTemplate);

}


void doCreate() {

}


void doBuild() {
    // Initial configuration
    readPOM();
    readApplicationProperties();

    std::string buildCommand = "g++ src/cpp/*.cpp target/*.cpp -Isrc/cpp ";
    analyzeDependencies(&buildCommand);

    // Generate applicationProperties.cpp
    std::string applicationPropertiesTemplate = readTextFile(programDirectory + "/templates/applicationProperties.cpp");
    // std::cout << applicationPropertiesTemplate << std::endl;
    insertElementIntoTemplate(&applicationPropertiesTemplate, "data-appname", appName);
    
    

    auto itetator = applicationProperties.begin();
    while (itetator != applicationProperties.end()) {
        // std::cout << "Key = \"" << itetator -> first << "\", Value = \"" << itetator -> second << "\"" << std::endl;
        repeatElement(&applicationPropertiesTemplate, "0");
        insertElementIntoTemplate(&applicationPropertiesTemplate, "data-key", itetator -> first);
        insertElementIntoTemplate(&applicationPropertiesTemplate, "data-value", itetator -> second);
        itetator ++;
    }
    removeRepeatTag(&applicationPropertiesTemplate, "0");
    // std::cout << applicationPropertiesTemplate << std::endl;
    writeTextFile("target/applicationProperties.cpp", applicationPropertiesTemplate);

    //insertRepeatedElementIntoTemplate(&applicationPropertiesTemplate, "{{data-key}}", "`122");

    readBanner();
    
    // Define application name
    if (appName == "") {
        buildCommand += "-o out/Application";
    } else {
        buildCommand += "-o out/" + appName;
    }
        
    // Build project
    system(buildCommand.c_str());
    std::cout << "Build complete." << std::endl;
}


void doRun() {
    readPOM();
    std::string targetUri = "./out/";
    system((targetUri + appName).c_str());
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
            std::cout << item << std::endl;
        }
    } else {
        std::cout << "Unsupported argument \"" << arg << "\"" << std::endl;
    }
}


int main(int argc, char* argv[]) {
    // Get the location where the cli-tool exists
    char buffer[1024];
    readlink("/proc/self/exe", buffer, 1024);
    programDirectory = buffer;
    programDirectory = programDirectory.substr(0, programDirectory.length() - strlen(argv[0]) - 1);
    // std::cout << "cli@" << programDirectory << std::endl;

    // Handle with opereation command
    if (argc < 2) {
        return 0;
    } else if (strcmp(argv[1], "create") == 0) {
        doCreate();
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