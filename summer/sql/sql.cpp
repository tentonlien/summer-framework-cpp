/* Created by Tenton Lien on 4/7/2019 */

#include "sql.h"

extern std::vector<std::vector<std::string>> mysql(std::string, std::string);

Sql::Sql(std::string dbName) {
    this -> dbName = dbName;
}

int Sql::query(std::string sqlQuery) {
    this -> result = mysql(this -> dbName, sqlQuery);
    return 0;
}