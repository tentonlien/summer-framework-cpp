/* Created by Tenton Lien on 5/7/2019 */

#ifndef JSON_H
#define JSON_H

#include <string>

// RapidJSON header
#include "com.tencent.rapidjson.1.10/document.h"
#include "com.tencent.rapidjson.1.10/writer.h"
#include "com.tencent.rapidjson.1.10/stringbuffer.h"

class JsonParser {
  public:
    JsonParser();
    std::string getKey(std::string);
    int setKey(std::string, std::string);
    int createKey(std::string, std::string);
    std::string toString();  // Converting JSON object to string

  private:
    rapidjson::Document document;
};

#endif