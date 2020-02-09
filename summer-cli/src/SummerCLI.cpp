/* Created by Tenton Lien on 4/11/2019 */

#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <unistd.h>
#include <vector>
 
#include "ProjectInitializer.h"
#include "ProjectBuilder.h"
#include "SummerCLI.h"

const std::string cliVersion = "0.0.1";

bool detailMode = true;

std::string programDirectory;
std::string projectName = "";


void doRun() {
    // readPOM();
    std::string targetUri = "cd ./out && ./";
    int status = system((targetUri + projectName).c_str());
    if (status == 256) {
        std::cout << "Error: Failed to run the target program" << std::endl;
    }
}


int main(int argc, char* argv[]) {
    // Get the location where the cli-tool exists
    char buffer[1024];
    ssize_t status = readlink("/proc/self/exe", buffer, 1024);
    if (status == -1) {
        std::cout << "Error: cannot get the location where the cli-tool exists" << std::endl;
    }

    programDirectory = buffer;
    programDirectory = programDirectory.substr(0, programDirectory.length() - strlen(argv[0]) - 1);

    // Handle with opereation command
    if (argc < 2) {
        std::cout << "usage: summer [--help] [--version]" << std::endl;
        std::cout << "       <command> [<args>]" << std::endl << std::endl;
        std::cout << "Available commands are:" << std::endl << std::endl;
        std::cout << "  run [options] <files> [--] [args]" << std::endl;
        std::cout << "    Run a summer project executable" << std::endl << std::endl;
        return 0;
    }
    
    // summer init --dependencies=web,data-sql your-project
    else if (strcmp(argv[1], "init") == 0) {
        if (argc < 3) {
            std::cout << "summer: \033[40;1;31merror\033[0m: project name required" << std::endl << std::endl;
            std::cout << "To initialize a new Summer project, use \"summer init <project-name>\"." << std::endl;
        } else {
            projectName = argv[2];
            ProjectInitializer projectInitializer;
        }
    }
    
    else if (strcmp(argv[1], "build") == 0) {
        ProjectBuilder projectBuilder;
    }
    
    else if (strcmp(argv[1], "run") == 0) {
        doRun();
    }
    
    else if (strcmp(argv[1], "list") == 0) {
        if (argc == 3) {
            // doList(argv[2]);
        }
    }
    
    else if (strcmp(argv[1], "version") == 0) {
        std::cout << "Summer CLI v" << cliVersion << std::endl;
    }
    return 0;
}