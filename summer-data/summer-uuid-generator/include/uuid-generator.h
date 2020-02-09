/* Created by Tenton Lien on 6/8/2019 */

#define SUMMER_UUID_GENERATOR_H
#ifdef SUMMER_UUID_GENERATOR_H

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <string>

class UUIDGenerator {
  public:
    static std::string generate();

  private:
    static const int len = 32;
    static unsigned char random_char();
};

#endif