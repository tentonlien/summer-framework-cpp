#ifndef METHODS_H
#define METHODS_H

#include <string>

class Method {
    public:
        int GET = 0;
        int POST = 1;

        Method(std::string);
};

#endif