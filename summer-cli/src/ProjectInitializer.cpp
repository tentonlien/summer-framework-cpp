/* Created by Tenton Lien on 12/13/2019 */

#include <cstring>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "ProjectInitializer.h"
#include "SummerCLI.h"
#include "TemplateProcessor.h"

ProjectInitializer::ProjectInitializer() {
    // Create the project directory
    std::vector<std::string> commands;
    commands.push_back("cp -r " + programDirectory + "/template/project-template " + projectName);
    std::string programEntryFileName = projectName;
    if (programEntryFileName[0] > 'Z') {
        programEntryFileName[0] -= 32;
    }
    commands.push_back("mv " + projectName + "/src/cpp/Application.cpp " + projectName + "/src/cpp/" + programEntryFileName + "Application.cpp ");
    
    // Run script commands
    for (unsigned int i = 0; i < commands.size(); i ++) {
        if (system(commands[i].c_str()) == -1) {
            std::cerr << "Build failed" << std::endl;
        }
    }

    // Update makefile
    TemplateProcessor templateProcessor(projectName + "/Makefile");
    templateProcessor.insertElement("projectName", projectName);
    templateProcessor.insertElement("programEntryFileName", programEntryFileName);
    templateProcessor.insertElement("programEntryFileName2", programEntryFileName);
    templateProcessor.output(projectName + "/Makefile");

    // Update pom.json
    TemplateProcessor templateProcessor2(projectName + "/pom.json");
    templateProcessor2.insertElement("projectName", projectName);
    templateProcessor2.insertElement("projectVersion", "0.0.1");
    templateProcessor2.insertElement("projectAuthor", "");
    templateProcessor2.output(projectName + "/pom.json");
    
    std::cout << "Initial complete." << std::endl;
}