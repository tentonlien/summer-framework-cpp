/* Created by Tenton Lien on 1/12/2020 */

#include "SummerCLI.h"
#include "ProjectObjectModel.h"

ProjectObjectModel::ProjectObjectModel() {
    std::ifstream fin("pom.json");
	json pomObject;
    fin >> pomObject;
    fin.close();

    this -> projectName = pomObject["project"]["name"];
    this -> projectVersion = pomObject["project"]["version"];
    this -> projectAuthor = pomObject["project"]["author"];
    for (json::iterator it = pomObject["dependencies"].begin(); it != pomObject["dependencies"].end(); ++it) {
        this -> dependencies.push_back((*it)["id"]);
    }
    
}

ProjectObjectModel::ProjectObjectModel(std::string projectName) {

}

void ProjectObjectModel::output() {
    json jsonObject = this -> getJsonObject();
}

void ProjectObjectModel::print() {
    json jsonObject = this -> getJsonObject();
    std::cout << jsonObject.dump() << std::endl;
}

json ProjectObjectModel::getJsonObject() {
    json jsonObject;
    jsonObject["project"]["name"] = this -> projectName;
    jsonObject["project"]["author"] = this -> projectAuthor;
    jsonObject["project"]["version"] = this -> projectVersion;
    jsonObject["dependencies"] = this -> dependencies;
    return jsonObject;
}