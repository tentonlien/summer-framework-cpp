#include "summer.h"
using namespace std;

#ifndef USER_ENTITY_CPP
#define USER_ENTITY_CPP

class UserEntity {
  public:
    string getName() {
        return this -> name;
    }

    void setName(string name) {
        this -> name = name;
    }

    string getPassword() {
        return this -> password;
    }

    void setPassword(string password) {
        this -> password = password;
    }

  private:
    string name;
    string password;
};

#endif