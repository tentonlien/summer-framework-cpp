/* Created by Tenton Lien on 1/12/2020 */

#ifndef PROJECT_OBJECT_MODEL_H
#define PROJECT_OBJECT_MODEL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann-json/json.hpp>

using json = nlohmann::json;

class ProjectObjectModel {
  public:
    std::string projectName;
    std::string projectVersion;
    std::string projectAuthor;
    std::vector<std::string> dependencies;

    ProjectObjectModel();  // for Project Builder
    ProjectObjectModel(std::string);  // for Project Initializer
    void output();
    void print();

  private:
    json getJsonObject();
};


#endif