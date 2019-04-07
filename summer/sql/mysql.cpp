/* Created by Tenton Lien on 4/7/2019 */

#include <mysql.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "../summer.h"

std::vector<std::vector<std::string>> mysql(std::string dbName, std::string sqlQuery) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    std::vector<std::vector<std::string>> result;

    /* Connect to database */
    if (!mysql_real_connect(conn, param_mysql_host,
                            param_mysql_user, 
                            param_mysql_password, 
                            (char*)(dbName.c_str()), 
                            param_mysql_port, 
                            NULL, 0))
    {
        printLog(Logs.ERROR, mysql_error(conn));
        return result;
    }

    /* Send SQL query */
    if (mysql_query(conn, sqlQuery.c_str())) {
        printLog(Logs.ERROR, mysql_error(conn));
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