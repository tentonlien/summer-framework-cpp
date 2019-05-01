/* Created by Tenton Lien on 4/11/2019 */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include <dirent.h>
#include <unistd.h>

#include "tinyxml2.h"

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

std::string readTextFile(std::string path) {
    std::ifstream textFile(path);

    if (!textFile) {
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
    std::string::size_type pos = cppTemplate -> find(tag);
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
        *cppTemplate = result.prefix().str() + result.suffix().str();
    }
    return 0;
}

std::vector<std::string> getFiles(std::string cate_dir) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ptr;

    if ((dir = opendir(cate_dir.c_str())) == NULL) {
        std::cout << cate_dir << std::endl;
        perror("Open dir error...");
        exit(1);
    }
   
    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr -> d_name,".") == 0 || strcmp(ptr -> d_name, "..") == 0) {
            continue;
        } else if(ptr->d_type == 8) {  // File
            files.push_back(ptr -> d_name);
        } else if(ptr -> d_type == 10) {  // Link file
            continue;
        } else if(ptr -> d_type == 4) {  // Directory
            files.push_back(ptr -> d_name);
        }
    }  
    closedir(dir);

    std::sort(files.begin(), files.end());
    return files;
}


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
        } else if (elemName == "web") {
            for (tinyxml2::XMLElement* subElem = elem -> FirstChildElement(); subElem != NULL; subElem = subElem -> NextSiblingElement()) {
                std::string subElemName = subElem->Value();
                if (subElemName == "port") {
                    // param_web_port = subElem -> FirstChild() -> ToText() -> Value();
                }
            }
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
        } else if (dependencies[i].name == "mysql-connector-c") {
            // *buildCommand += programDirectory + "/repository/" + dependencies[i].path +"/libmysqlclient.so.20 -L" + programDirectory + "/repository/" + dependencies[i].path + " ";
            // *buildCommand += "$(mysql_config --cflags) $(mysql_config --libs) ";
        }
    }
}


// Read data from src/resources/application.properties
void readApplicationProperties() {
    std::string applicationPropertiesText = readTextFile("src/resources/application.properties");
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
    std::string bannerTemplate = readTextFile(programDirectory + "/template/banner.cpp");
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

    insertElementIntoTemplate(&bannerTemplate, "banner-text", bannerText);
    writeTextFile("target/banner.cpp", bannerTemplate);

}


void doCreate() {

}


void doBuild() {
    // Initial configuration
    readPOM();
    readApplicationProperties();

    std::string buildCommand = "cd ./out && g++ ../src/cpp/*.cpp ../target/*.cpp -I ../src/cpp ";
    analyzeDependencies(&buildCommand);

    // Generate applicationProperties.cpp
    std::string applicationPropertiesTemplate = readTextFile(programDirectory + "/template/applicationProperties.cpp");
    insertElementIntoTemplate(&applicationPropertiesTemplate, "data-appname", appName);
    
    auto itetator = applicationProperties.begin();
    while (itetator != applicationProperties.end()) {
        repeatElement(&applicationPropertiesTemplate, "0");
        insertElementIntoTemplate(&applicationPropertiesTemplate, "data-key", itetator -> first);
        insertElementIntoTemplate(&applicationPropertiesTemplate, "data-value", itetator -> second);
        itetator ++;
    }
    removeRepeatTag(&applicationPropertiesTemplate, "0");
    writeTextFile("target/applicationProperties.cpp", applicationPropertiesTemplate);

    readBanner();
    
    // Define application name
    if (appName == "") {
        buildCommand += "-o Application ";
    } else {
        buildCommand += "-o " + appName + " ";
    }

    buildCommand += "-Wl,-rpath ./lib ";
        
    // Build project
    int status = system(buildCommand.c_str());
    //std::cout << "Status: " << status << std::endl;
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