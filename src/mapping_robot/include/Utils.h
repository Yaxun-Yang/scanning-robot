#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
namespace stereye {
namespace utils {
/**
 * \brief  Recursivly make dirs
 *
 * \param path (path to make dir)
 * \return true for succeed, false for failed
 */
static bool mkdirs(const std::string& path) {
    printf("path:%s\n",path.c_str());
    char str[512];
    strncpy(str, path.c_str(), 512);
    int len = strlen(str);
    // clear error
    errno = 0;
    // check folders between / and /
    // i = 1 aims to remove first /
    for (int i = 1; i < len; ++i) {
        if (str[i] == '/') {
            str[i] = '\0';
            if (access(str, 0) == -1) {
                if (mkdir(str, S_IRWXU)) {
                    if (errno != EEXIST) {
                        printf("mkdir: %s failed!", str);
                        return false;
                    }
                }
            }
            str[i]='/';
        }
    }
    // check last folder
    if (len > 0 && access(str, 0) == -1) {
        if (mkdir(str, S_IRWXU)) {
            if (errno != EEXIST) {
                printf("mkdir: %s failed!", str);
                return false;
            }
        }
    }
    return true;
}
} // namespace utils
} // namespace stereye