/* Created by Tenton Lien on 4/6/2019 */

#ifndef SUMMER_H
#define SUMMER_H

#include <string>
#include "sql/sql.h"

// Global params
extern std::string param_app_name;
extern unsigned int param_app_port;

extern char* param_mysql_host;
extern unsigned int param_mysql_port;
extern char* param_mysql_user;
extern char* param_mysql_password;


typedef unsigned char Method;

const struct {
    unsigned char GET = 0;
    unsigned char POST = 1;
    unsigned char PUT = 2;
    unsigned char PATCH = 3;
    unsigned char DELETE = 4;
    unsigned char COPY = 5;
    unsigned char HEAD = 6;
    unsigned char OPTIONS = 7;
    unsigned char LINK = 8;
    unsigned char UNLINK = 9;
    unsigned char PURGE = 10;
    unsigned char LOCK = 11;
    unsigned char UNLOCK = 12;
    unsigned char PROPFIND = 13;
    unsigned char VIEW = 14;
    unsigned char UNKNOWN = 15;
} Methods;


typedef std::string Log;

const struct {
    std::string INFO = "INFO";
    std::string WARNING = "WARNING";
    std::string ERROR = "ERROR";
    std::string FATAL_ERROR = "FATAL_ERROR";
} Logs;

extern void printLog(Log, std::string);

#endif