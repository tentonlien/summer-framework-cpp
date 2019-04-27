/* Created by Tenton Lien on 4/16/2019 */

#include "cache.h"

int Cache::set(std::string key, std::string value) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return 0;
    } else {
        data.insert({key, value});
        return 1;
    }
}


std::string Cache::get(std::string key) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return "";
    } else {
        return iterator -> second;
    }
}


int Cache::strlen(std::string key) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return -1;
    } else {
        return (iterator -> second).length();
    }
}


int Cache::append(std::string key, std::string value) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return 0;
    } else {
        iterator -> second += value;
        return 1;
    }
}


int Cache::del(std::string key) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return 0;
    } else {
        data.erase(iterator);
        return 1;
    }
}


long long Cache::incr(std::string key) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return -1;
    } else {
        std::string::size_type sz;
        long long result = std::stoll(iterator -> second, &sz) + 1;
        iterator -> second = std::to_string(result);
        return result;
    }
}


long long Cache::decr(std::string key) {
    auto iterator = data.find(key);
    if (iterator == data.end()) {
        return -1;
    } else {
        std::string::size_type sz;
        long long result = std::stoll(iterator -> second, &sz) - 1;
        iterator -> second = std::to_string(result);
        return result;
    }
}