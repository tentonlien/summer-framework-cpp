/* Created by Tenton Lien on 4/7/2019 */

#ifndef SQL_H
#define SQL_H

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "mysql.h"

class SqlQueryResult {
  public:
    SqlQueryResult();
    bool hasNext();
    std::string getString(int);
    void createRow();
    void pushString(int, std::string);
  
  private:
    std::vector<std::vector<std::string>> result;
    int cursor;
};


class SqlConnector {
  public:
    SqlQueryResult sqlQueryResult;

    SqlConnector() {}
    SqlConnector(std::string) {}
    virtual ~SqlConnector() {}
    virtual void close() {}
    virtual int executeUpdate(std::string) {}
    virtual SqlQueryResult* executeQuery(std::string) {}

  protected:
    std::string host, port, dbName, user, password;
};


class MysqlConnector: public SqlConnector {
  public:
    MysqlConnector(std::string);
    ~MysqlConnector();

    void close();
    int executeUpdate(std::string);
    SqlQueryResult* executeQuery(std::string);
        

  private:
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
}; 


struct DatabaseConnectException: public std::exception {
  const char * what () const throw () {
    return "Can't connect to the database";
  }
};

#endif