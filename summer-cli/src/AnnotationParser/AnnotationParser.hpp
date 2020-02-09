/* Created by Tenton Lien on 5/8/2019 */

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

// #include <summer.h>

class Annotation {
  public:
    std::string annotationLine;
    std::string declarationLine;
};


class AnnotationParser {
  public:
    AnnotationParser() {}
    void scanAnnotations(std::string);
  protected:
    std::vector<Annotation> annotations;
    
};


void AnnotationParser::scanAnnotations(std::string uri) {
    std::ifstream ifs(uri);
    if (!ifs) {
        std::cout << "Read file failed: " << uri << std::endl;
    } else {
        std::string line;
        while (std::getline(ifs, line)) {
            if (std::regex_match(line, std::regex("[^\"]*///[\\D\\d]*"))) {
                Annotation annotation;
                annotation.annotationLine = line;
                std::getline(ifs, line);
                annotation.declarationLine = line;
                this -> annotations.push_back(annotation);
            }
        }
        ifs.close();
    }
}