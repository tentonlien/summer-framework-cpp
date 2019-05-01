/* Created by Tenton Lien on 4/7/2019 */

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// #include "application.h"
#include "sql.h"

MysqlConnector::MysqlConnector(std::string uri) {
    std::regex uriRegularExpression("[[:alnum:]]+://[A-Za-z0-9\\.]+:[A-Za-z0-9_/]+\\?user=[[:alnum:]]+&password=.+");
    if (!std::regex_match(uri, uriRegularExpression)) {
        std::cout << "Invalid URI: " + uri << std::endl;
        // throw DatabaseConnectException();
    } else {
        int pos, pos2;

        // Get database type
        pos = uri.find("://");
        if (pos != std::string::npos) {
            // this -> dbType = uri.substr(0, pos);
        }

        // Get host
        pos += 3;
        pos2 = uri.find(":", pos);
        if (pos2 != std::string::npos) {
            this->host = uri.substr(pos, pos2 - pos);
        }

        // Get port
        pos2 += 1;
        pos = uri.find("/", pos2);
        if (pos != std::string::npos) {
            this->port = uri.substr(pos2, pos - pos2);
        }

        // Get databse name
        pos += 1;
        pos2 = uri.find("?", pos);
        if (pos2 != std::string::npos) {
            this->dbName = uri.substr(pos, pos2 - pos);
        }

        // Get user
        pos2 += 6;
        pos = uri.find("&", pos2);
        if (pos != std::string::npos) {
            this->user = uri.substr(pos2, pos - pos2);
        }

        // Get password
        pos += 10;
        this -> password = uri.substr(pos, uri.length() - pos);

        conn = mysql_init(NULL);
        mysql_set_character_set(conn, "utf8");  
        if (!mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), (char *)(dbName.c_str()), 3306, NULL, 0))
        {
            throw DatabaseConnectException();
        }
    }
}


MysqlConnector::~MysqlConnector() {}


void MysqlConnector::close() {
    mysql_free_result(res);
    mysql_close(conn);
}


int MysqlConnector::executeUpdate(std::string sql) {}


SqlQueryResult* MysqlConnector::executeQuery(std::string sqlQuery) {
    if (mysql_query(conn, sqlQuery.c_str())) {
        std::string errorString = mysql_error(conn);
        if (errorString.empty()) {
            throw std::string("The MySQL query might be wrong");
        } else {
            throw errorString;
        }
    }

    res = mysql_store_result(conn);
    if (!res) {
        throw std::string("No result");
    }

    int lineCursor = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        sqlQueryResult.createRow();
        int num_fields = mysql_num_fields(res);
        for (int i = 0; i < num_fields; i ++) {
            if (row[i] == NULL) {
                sqlQueryResult.pushString(lineCursor, "NULL");
            } else {
                sqlQueryResult.pushString(lineCursor, row[i]);
            }
            
        }
        
        lineCursor ++;
    }
    return &(this -> sqlQueryResult);
}