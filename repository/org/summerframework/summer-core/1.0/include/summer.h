/* Created by Tenton Lien on 4/6/2019 */

#ifndef SUMMER_H
#define SUMMER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool readTextFile(std::string, std::string*);
bool writeTextFile(std::string, std::string);
std::vector<std::string> getFiles(std::string cate_dir);

#endif