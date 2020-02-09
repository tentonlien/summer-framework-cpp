/* Created by Tenton Lien on 1/9/2020 */

#ifndef SUMMER_DATA_IO_FILE_H
#define SUMMER_DATA_IO_FILE_H

#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>

struct IOException: public std::exception {
    const char* what() const throw() {
        return "IO operations failed";
    }
};

typedef struct FileItem {
    std::string fileName;
    char fileType;
};


// File
class File {
  public:

    static std::string readTextFile(std::string path) {
        std::ifstream textFile(path);

        if (!textFile) {
            throw IOException();
        }

        std::istreambuf_iterator<char> begin(textFile);
        std::istreambuf_iterator<char> end;
        std::string data(begin, end);
        textFile.close();
        return data;
    }


    static void writeTextFile(std::string path, std::string data) {
        std::ofstream textFile(path);
        if (!textFile) {
            throw IOException();
        }
        textFile << data;
        textFile.close();
    }

    static size_t getFileSize(const std::string& fileName){ 
        struct stat info;
        stat(fileName.c_str(), &info);
        size_t size = info.st_size;
        return size;  // unit: byte
    }


    static std::vector<FileItem> getFiles(std::string cate_dir) {
        std::vector<FileItem> fileItems;
        DIR *dir;
        struct dirent *ptr;

        if ((dir = opendir(cate_dir.c_str())) == NULL) {
            std::cout << "CANNOT READ '" << cate_dir << "'" << std::endl;
            throw IOException();
        }
   
        while ((ptr = readdir(dir)) != NULL) {
            
            if(strcmp(ptr -> d_name,".") == 0 || strcmp(ptr -> d_name, "..") == 0) {
                continue;
            } else {
                FileItem fileItem;
                fileItem.fileName = ptr -> d_name;
                if(ptr -> d_type == 8) {  // File
                    fileItem.fileType = 'f';
                    fileItems.push_back(fileItem);
                } else if(ptr -> d_type == 10) {  // Link file
                    fileItem.fileType = 'l';
                    fileItems.push_back(fileItem);
                } else if(ptr -> d_type == 4) {  // Directory
                    fileItem.fileType = 'd';
                    fileItems.push_back(fileItem);
                }
            }
             
        }
        closedir(dir);

        //std::sort(files.begin(), files.end());
        return fileItems;
    }
};

#endif