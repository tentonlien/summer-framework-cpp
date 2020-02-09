/* Created by Tenton Lien on 5/8/2019 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "AnnotationParser.hpp"

class RequestMapping {
  public:
    std::string method;
    std::string value;
    std::string functionName;
    std::string returnType;
};


class RestController {
  public:
    std::string name;
    std::vector<RequestMapping> requestMappings;

    void addRequestMapping(RequestMapping requestMapping) {
        requestMappings.push_back(requestMapping);
    }
};


class RestControllerAnnotationParser: public AnnotationParser {
  public:
    RestController restController;

    void parse();
    void print();
    
  private:
    void parseRestController(Annotation);
    void parseRequestMapping(Annotation);
};


void RestControllerAnnotationParser::parseRestController(Annotation annotation) {
    if (!std::regex_match(annotation.declarationLine, std::regex(".*class[\\D\\d]*"))) {
        // TO-DO: Handle error
        std::cout << "Error: " << annotation.declarationLine << std::endl;
    } else {
        size_t pos = annotation.declarationLine.find("class ");
        if (pos == std::string::npos) {
            // Error
        } else {
            size_t pos2 = pos + 6;  // Skip "class "
            while (annotation.declarationLine[pos2] != ' ' && pos2 < annotation.declarationLine.length()) {
                pos2 ++;
            }

            this -> restController.name = annotation.declarationLine.substr(pos + 6, pos2 -pos - 6);
        }
    }
}


void RestControllerAnnotationParser::parseRequestMapping(Annotation annotation) {
    RequestMapping requestMapping;

    // Single-param mode
    if (std::regex_match(annotation.annotationLine, std::regex(".*RequestMapping\\(\".*\"\\)[\\D\\d]*"))) {
        

        size_t pos = annotation.annotationLine.find("\"");
        if (pos == std::string::npos) {
            // Error
        } else {
            size_t pos2 = pos + 1;  // Skip "\""
            while (annotation.annotationLine[pos2] != '\"' && pos2 < annotation.annotationLine.length()) {
                pos2 ++;
            }

            requestMapping.value = annotation.annotationLine.substr(pos + 1, pos2 -pos - 1);
            requestMapping.method = "*";
        }
    }

    // Multi-param mode
    else {
        // Parse value
        size_t pos = annotation.annotationLine.find("value");
        if (pos != std::string::npos) {
            while (annotation.annotationLine[pos] != '\"' && pos < annotation.annotationLine.length()) {
                pos ++;
            }
            
            size_t pos2 = pos + 1;  // Skip "\""
            while (annotation.annotationLine[pos2] != '\"' && pos2 < annotation.annotationLine.length()) {
                pos2 ++;
            }

            requestMapping.value = annotation.annotationLine.substr(pos + 1, pos2 -pos - 1);
        }

        // Parse method
        pos = annotation.annotationLine.find("method");
        if (pos != std::string::npos) {
            pos = annotation.annotationLine.find("=", pos);

            while (isalpha(annotation.annotationLine[pos]) && pos < annotation.annotationLine.length()) {
                pos ++;
            }
            
            size_t pos2 = pos;
            while (annotation.annotationLine[pos2] != ')' && pos2 < annotation.annotationLine.length()) {
                pos2 ++;
            }
            
            requestMapping.method = annotation.annotationLine.substr(pos + 1, pos2 -pos - 1);
        }
    }

    // Parse function declaration
    std::regex tokenRE("[A-Za-z0-9:]+");
    std::smatch result;
    std::string temp = annotation.declarationLine;

    // Parse return type
    if (std::regex_search(temp, result, tokenRE)) {
        requestMapping.returnType = result.str();
        temp = result.suffix().str();
    }

    // Parse function name
    if (std::regex_search(temp, result, tokenRE)) {
        requestMapping.functionName = result.str();
        temp = result.suffix().str();
    }

    this -> restController.addRequestMapping(requestMapping);
}


void RestControllerAnnotationParser::parse() {
    for (size_t i = 0; i < this -> annotations.size(); i ++) {
        if (this -> annotations[i].annotationLine.find("RestController") != std::string::npos) {
            this -> parseRestController(this -> annotations[i]);
        } else if (this -> annotations[i].annotationLine.find("RequestMapping") != std::string::npos) {
            this -> parseRequestMapping(this -> annotations[i]);
        }
    }
}


void RestControllerAnnotationParser::print() {
    std::cout << "RestController, class(name=\"" << this -> restController.name << "\")" << std::endl;
    for (size_t i = 0; i < this -> restController.requestMappings.size(); i ++) {
        std::cout << "---- " << "RequestMapping(";
        std::cout << "value=\"" << this -> restController.requestMappings[i].value << "\", ";
        std::cout << "method=\"" << this -> restController.requestMappings[i].method << "\"";
        std::cout << "), fun(name=\"" << this -> restController.requestMappings[i].functionName << "\", ";
        std::cout << "retype=\"" << this -> restController.requestMappings[i].returnType << "\"";
        std::cout << ")" << std::endl;
    }
}