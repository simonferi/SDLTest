#ifndef HELPER_H
#define HELPER_H

#include <string>

class Helper {
public:
    static std::string absolutePath(const std::string relativePath) {
        std::string basePath(SDL_GetBasePath());
        return basePath + relativePath;
    }
};


#endif // HELPER_H
