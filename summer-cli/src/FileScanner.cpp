/* Created by Tenton Lien on 1/13/2020 */

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include <org/summerframework/data/io.h>
#include "FileScanner.h"


#include <nlohmann-json/json.hpp>

using json = nlohmann::json;

FileScanner::FileScanner() {
    this -> scan();
}

void FileScanner::scan() {
    this -> scan("./");
}

void FileScanner::scan(std::string path) {
    // Ignore files after gen/ and out/
    if (path == "./gen/" || path == "./out/") {
        return;
    }
    std::vector<FileItem> fileItems = File::getFiles(path);
    for (unsigned int i = 0; i < fileItems.size(); i ++) {
        if (fileItems[i].fileType == 'f') {
            std::cout << fileItems[i].fileName << " " << fileItems[i].fileType << std::endl;
        } else if (fileItems[i].fileType == 'd') {
            scan(path + fileItems[i].fileName + "/");
        }
        
    }
}