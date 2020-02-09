/* Created by Tenton Lien on 1/5/2020 */

#include <iostream>
#include "SerializedObject.h"

void SerializedObject::addDeclaredField(std::string fieldName, int* fieldValue) {
    std::any value = fieldValue;
    this->declaredFields.insert({fieldName, fieldValue});
}


void SerializedObject::addDeclaredField(std::string fieldName, double* fieldValue) {
    std::any value = fieldValue;
    this->declaredFields.insert({fieldName, fieldValue});
}


void SerializedObject::addDeclaredField(std::string fieldName, bool* fieldValue) {
    std::any value = fieldValue;
    this->declaredFields.insert({fieldName, fieldValue});
}


void SerializedObject::addDeclaredField(std::string fieldName, std::string* fieldValue) {
    std::any value = fieldValue;
    this->declaredFields.insert({fieldName, fieldValue});
}

void SerializedObject::addDeclaredField(std::string fieldName, SerializedObject* fieldValue) {
    std::any value = fieldValue;
    this->declaredFields.insert({fieldName, fieldValue});
}

json SerializedObject::getJsonObject() {
    json jsonObject;
    for (auto iter = declaredFields.begin(); iter != declaredFields.end(); iter++) {
        if (iter->second.type() == typeid(int*)) {
            jsonObject[iter->first] = *(std::any_cast<int*>(iter->second));
        } else if (iter -> second.type() == typeid(std::string*)) {
            jsonObject[iter->first] = *(std::any_cast<std::string*>(iter -> second));
        } else {
            jsonObject[iter->first] = (std::any_cast<SerializedObject*>(iter -> second)) -> getJsonObject();
        }
    }
    return jsonObject;
}

std::string SerializedObject::serialize() {
    json jsonObject;
    for (auto iter = declaredFields.begin(); iter != declaredFields.end(); iter++) {
        if (iter->second.type() == typeid(int*)) {
            jsonObject[iter->first] = *(std::any_cast<int*>(iter->second));
        } else if (iter -> second.type() == typeid(std::string*)) {
            jsonObject[iter->first] = *(std::any_cast<std::string*>(iter -> second));
        } else {
            jsonObject[iter->first] = (std::any_cast<SerializedObject*>(iter -> second)) -> getJsonObject();
        }
    }
    return jsonObject.dump();
}