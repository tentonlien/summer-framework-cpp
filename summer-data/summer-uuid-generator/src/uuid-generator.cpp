/* Created by Tenton Lien on 6/8/2019 */

#include "uuid-generator.h"

unsigned char UUIDGenerator::random_char() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 255);
    return static_cast<unsigned char>(dis(gen));
}

std::string UUIDGenerator::generate() {
    std::stringstream ss;
    for(auto i = 0; i < len; i++) {
        auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << int(rc);
        auto hex = hexstream.str(); 
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }        
    return ss.str();
}