/* Created by Tenton Lien on 5/7/2019 */

#include <iostream>
#include "json.h"

int main() {
    // Initializing a JSON object
    JsonParser jsonParser;

    // Adding keys
    jsonParser.createKey("name", "Tom");
    jsonParser.createKey("age", "20");
    jsonParser.createKey("gender", "Female");

    // Converting the JSON object to String
    std::cout << jsonParser.toString() << std::endl;
    return 0;
}
