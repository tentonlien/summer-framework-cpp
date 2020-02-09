/* Created by Tenton Lien on 12/14/2019 */

#ifndef TEMPLATE_PROCESSOR_H
#define TEMPLATE_PROCESSOR_H

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

class TemplateProcessor {
  public:
    TemplateProcessor(std::string);

    int insertElement(std::string tag, std::string value);

    int insertRepeatedElement(std::string tagId, std::string tag, std::string value);

    int removeRepeatTag();

    std::string* getTemplateContentPointer();

    int output(std::string url);

    void print();


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
            std::cout << "Tag not found: " << tag << std::endl;
            return -1;
        }
        return 0;
    }
};


#endif