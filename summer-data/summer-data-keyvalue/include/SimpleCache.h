/* Summer Cache conforms basic rules of Redis */
/* Created by Tenton Lien on 4/16/2019 */

#define SUMMER_DATA_KEYVALUE_SIMPLECACHE_H
#ifdef SUMMER_DATA_KEYVALUE_SIMPLECACHE_H

#include <map>
#include <string>

class SimpleCache {
    public:
        int set(std::string, std::string);     // SET key value
        std::string get(std::string);          // GET key
        int del(std::string);                  // DEL key
        int strlen(std::string);               // STRLEN key
        long long incr(std::string);           // INCR key
        long long decr(std::string);           // DECR key
        int append(std::string, std::string);  // APPEND key value

    private:
        std::map<std::string, std::string> data;
};

#endif