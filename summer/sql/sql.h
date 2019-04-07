/* Created by Tenton Lien on 4/7/2019 */

#ifndef SQL_H
#define SQL_H

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

#endif