/* Created by Tenton Lien on 12/14/2019 */

#ifndef PROJECT_BUILDER_H
#define PROJECT_BUILDER_H

#include <string>
#include <regex>
#include <map>

#include "ProjectObjectModel.h"

class ProjectBuilder {
  public:
    ProjectObjectModel* projectObjectModel;

    ProjectBuilder();
    ~ProjectBuilder();

  private:
    void generateApplicationProperties();
    void generateBanner();
    void generateBeanFactory();
    bool generateRouter();
        
    void updateLibrary();
};


#endif