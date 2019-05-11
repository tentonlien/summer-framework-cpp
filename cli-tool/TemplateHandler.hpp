/* Created by Tenton Lien on 5/8/2019 */

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "summer.h"

class TemplateHandler {
  public:
    TemplateHandler(std::string url) {
       readTextFile(url, &(this -> templateContent));  // Handle error
    }

    int insertElement(std::string tag, std::string value) {
        this -> insertElement(&(this -> templateContent), tag, value);
        return 0;
    }

    int insertRepeatedElement(std::string tagId, std::string tag, std::string value) {
        std::regex regRepeatedElement("\\{\\{repeat-start id=" + tagId + "\\}\\}[\\D\\d]*?\\{\\{repeat-end\\}\\}");
        std::smatch result;
        if (std::regex_search(this -> templateContent, result, regRepeatedElement)) {
            // std::cout << result.str() << std::endl;
            std::string temp = result.str();
            this -> insertElement(&temp, "repeat-start id=" + tagId, "");
            this -> insertElement(&temp, "repeat-end", "");
            this -> templateContent = result.prefix().str() + temp + "\n" + result.str() + result.suffix().str();
        }
        this -> insertElement(tag, value);
        return 0;
    }

    int removeRepeatTag() {
        std::regex regRepeatedElement("\\{\\{repeat-start id=[\\d]+\\}\\}[\\D\\d]*?\\{\\{repeat-end\\}\\}");
        std::smatch result;
        while (std::regex_search(this -> templateContent, result, regRepeatedElement)) {
            this -> templateContent = result.prefix().str() + result.suffix().str();
        }
        return 0;
    }

    std::string* getTemplateContentPointer() {
        return &(this -> templateContent);
    }

    int output(std::string url) {
        this -> removeRepeatTag();
        writeTextFile(url, this -> templateContent);
        return 0;
    }

    void print() {
        this -> removeRepeatTag();
        std::cout << this -> templateContent << std::endl;
    }


  private:
    std::string templateContent;

    int insertElement(std::string* temp, std::string tag, std::string value) {
        tag = "{{" + tag + "}}";
        std::string::size_type pos = temp -> find(tag);
        if (pos != std::string::npos) {
            // std::cout << "pos " << pos << std::endl;
            temp -> replace(pos, tag.length(), value);
            //std::cout << "$" << value << "$" << std::endl;
        } else {
            std::cout << "Tag not found" << std::endl;
            return -1;
        }
        return 0;
    }
};