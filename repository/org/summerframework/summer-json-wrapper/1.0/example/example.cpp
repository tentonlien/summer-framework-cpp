/* Created by Tenton Lien on 5/7/2019 */

#include <iostream>
#include "json.h"

using namespace std;

int main() {
    // Initializing a JSON object
    JsonParser jsonParser;

    // Adding keys
    jsonParser.createKey("name", "Tom");
    jsonParser.createKey("age", "20");
    jsonParser.createKey("gender", "Female");

    // Converting the JSON object to String
    cout << jsonParser.toString() << endl;
    return 0;
}
