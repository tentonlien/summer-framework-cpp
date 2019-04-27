/* Created by Tenton Lien on 4/7/2019 */

#include <mysql.h>
#include "sql.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "application.h"

std::vector<std::vector<std::string>> mysql(std::string dbName, std::string sqlQuery) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    std::vector<std::vector<std::string>> result;

    /* Connect to database */
    if (!mysql_real_connect(conn,
                            application.getProperty<std::string>("summer.datasource.url").c_str(), 
                            application.getProperty<std::string>("summer.datasource.username").c_str(), 
                            application.getProperty<std::string>("summer.datasource.password").c_str(), 
                            (char*)(dbName.c_str()), 
                            3306, 
                            NULL, 0))
    {
        // LogMessage errorConnect("", LogMessageType.ERROR, mysql_error(conn));
        throw DatabaseConnectException();
        // return result;
    }

    /* Send SQL query */
    if (mysql_query(conn, sqlQuery.c_str())) {
        // LogMessage errorQuery("", LogMessageType.ERROR, mysql_error(conn));
        return result;
    }
    res = mysql_use_result(conn);

    /* Organize result data */
    while ((row = mysql_fetch_row(res)) != NULL) {
        std::vector<std::string> line;
        for (int i = 0; row[i] != NULL; i ++) {
            line.push_back(row[i]);
        }
        result.push_back(line);
    }

    /* Close connection */
    mysql_free_result(res);
    mysql_close(conn);

    return result;
}