/* Created by Tenton Lien on 5/8/2019 */

#include "SummerCLI.h"
#include "TemplateProcessor.h"

    TemplateProcessor::TemplateProcessor(std::string url) {
       this -> templateContent = File::readTextFile(url);  // Handle error
       
    }

    int TemplateProcessor::insertElement(std::string tag, std::string value) {
        this -> insertElement(&(this -> templateContent), tag, value);
        return 0;
    }

    int TemplateProcessor::insertRepeatedElement(std::string tagId, std::string tag, std::string value) {
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

    int TemplateProcessor::removeRepeatTag() {
        std::regex regRepeatedElement("\\{\\{repeat-start id=[\\d]+\\}\\}[\\D\\d]*?\\{\\{repeat-end\\}\\}");
        std::smatch result;
        while (std::regex_search(this -> templateContent, result, regRepeatedElement)) {
            this -> templateContent = result.prefix().str() + result.suffix().str();
        }
        return 0;
    }

    std::string* TemplateProcessor::getTemplateContentPointer() {
        return &(this -> templateContent);
    }

    int TemplateProcessor::output(std::string url) {
        this -> removeRepeatTag();
        File::writeTextFile(url, this -> templateContent);
        return 0;
    }

    void TemplateProcessor::print() {
        this -> removeRepeatTag();
        std::cout << this -> templateContent << std::endl;
    }