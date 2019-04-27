/* Created by Tenton Lien on 4/7/2019 */

#ifndef SQL_H
#define SQL_H

#include <exception>
#include <string>
#include <vector>

class Sql {
    public:
        std::vector<std::vector<std::string>> result;

        Sql(std::string);
        int query(std::string);

    private:
        std::string dbName;
};


struct DatabaseConnectException: public std::exception {
  const char * what () const throw ()
  {
    return "Can't connect to the database";
  }
};

#endif