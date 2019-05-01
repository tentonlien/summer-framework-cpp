/* Created by Tenton Lien on 4/29/2019 */

#include <exception>
#include "sql.h"

SqlQueryResult::SqlQueryResult() {
    this -> cursor = -1;
}


bool SqlQueryResult::hasNext() {
    this -> cursor ++;
    if (this -> cursor >= result.size()) {
        return false;
    }
    return true;
}


std::string SqlQueryResult::getString(int columnIndex) {
    if (columnIndex >= result.at(cursor).size()) {
        return "";
    }
    return result.at(cursor).at(columnIndex);
}


void SqlQueryResult::pushString(int rowIndex, std::string value) {
    this -> result.at(rowIndex).push_back(value);
}


void SqlQueryResult::createRow() {
    std::vector<std::string> temp;
    this -> result.push_back(temp);
}