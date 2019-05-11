/* Summer: A C++ MVC Framework for Web Application on Linux Server */
/* Summer: Linux服务器上的C++网络应用MVC框架 */
/* Created by Tenton Lien on 4/6/2019 */

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "summer.h"

bool readTextFile(std::string path, std::string* data) {
    std::ifstream textFile(path);

    if (!textFile) {
        std::cerr << "Failed to read file: " << path << std::endl;
        return false;
    }

    std::istreambuf_iterator<char> begin(textFile);
    std::istreambuf_iterator<char> end;
    std::string fileContent(begin, end);
    textFile.close();
    *data = fileContent;
    return true;
}   


bool writeTextFile(std::string path, std::string data) {
    std::ofstream textFile(path);
    if (!textFile) {
        std::cerr << "Failed to open file while writing" << std::endl;
        return -1;
    }
    textFile << data;
    textFile.close();
    return 0;
}


std::vector<std::string> getFiles(std::string cate_dir) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ptr;

    if ((dir = opendir(cate_dir.c_str())) == NULL) {
        std::cout << cate_dir << std::endl;
        perror("Open dir error...");
        exit(1);
    }
   
    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr -> d_name,".") == 0 || strcmp(ptr -> d_name, "..") == 0) {
            continue;
        } else if(ptr->d_type == 8) {  // File
            files.push_back(ptr -> d_name);
        } else if(ptr -> d_type == 10) {  // Link file
            continue;
        } else if(ptr -> d_type == 4) {  // Directory
            files.push_back(ptr -> d_name);
        }
    }  
    closedir(dir);

    std::sort(files.begin(), files.end());
    return files;
}