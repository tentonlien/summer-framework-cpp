#include <iostream>
#include <string>
#include "application.h"

Application::Application() {
{{repeat-start id=0}}    this -> properties.insert({"{{data-key}}", "{{data-value}}"});{{repeat-end}}
    this -> setName("{{data-appname}}");
}