/* Created by Tenton Lien on 1/5/2020 */

#ifndef SERIALIZED_OBJECT_H
#define SERIALIZED_OBJECT_H

#include <any>
#include <unordered_map>
#include <string>

#include <nlohmann-json/json.hpp>

using json = nlohmann::json;

class SerializedObject {
  public:
    std::string objectName;

    void addDeclaredField(std::string, int*);
    void addDeclaredField(std::string, double*);
    void addDeclaredField(std::string, bool*);
    void addDeclaredField(std::string, std::string*);
    void addDeclaredField(std::string, SerializedObject*);

    json getJsonObject();
	  std::string serialize();

  private:
    std::unordered_map<std::string, std::any> declaredFields;
};

#endif