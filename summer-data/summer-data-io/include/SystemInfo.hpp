/* Created by Tenton Lien on 1/10/2020 */

#ifndef SUMMER_DATA_IO_SYSTEMINFO_H
#define SUMMER_DATA_IO_SYSTEMINFO_H

#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <exception>
#include <string>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <vector>

class SystemInfo {
  public:
    static std::string getHostName() {
        char hostname[60] = {'\0'};
        int res = gethostname(hostname, sizeof(hostname));
        return std::string(hostname);
    }

    static long getFreeMemorySize() {
        struct sysinfo tmp;
        int ret = sysinfo(&tmp);
        if (ret == 0) {
            return (unsigned long)tmp.freeram / (1024 * 1024);  // Unit: MB
        } else {
            return -1;
        }
    }

    static long getTotalMemorySize() {
        struct sysinfo tmp;
        int ret = sysinfo(&tmp);
        if (ret == 0) {
            return (unsigned long)tmp.totalram / (1024 * 1024);  // Unit: MB
        } else {
            return -1;
        }
    }

    static short getProcessAmount() {
        struct sysinfo tmp;
        int ret = sysinfo(&tmp);
        if (ret == 0) {
            return tmp.procs;
        } else {
            return -1;
        }
    }
};

#endif