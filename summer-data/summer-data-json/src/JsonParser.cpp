/* Created by Tenton Lien on 5/7/2019 */

#include "json.h"

JsonParser::JsonParser() {
    this -> document.SetObject();
}


std::string JsonParser::toString() {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}


std::string JsonParser::getKey(std::string) {
    return "";
}

int JsonParser::setKey(std::string key, std::string value) {
    /* rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
    rapidjson::Value rKey(rapidjson::kStringType);
    rapidjson::Value rValue(rapidjson::kStringType);
    rKey.SetString(key.c_str(), key.length(), allocator);
    rValue.SetString(value.c_str(), value.length(), allocator);
    document.AddMember(rKey, rValue, allocator); */
    return 0;
}

int JsonParser::createKey(std::string key, std::string value) {
    rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
    rapidjson::Value rKey(rapidjson::kStringType);
    rapidjson::Value rValue(rapidjson::kStringType);
    rKey.SetString(key.c_str(), key.length(), allocator);
    rValue.SetString(value.c_str(), value.length(), allocator);
    document.AddMember(rKey, rValue, allocator);
    return 0;
}