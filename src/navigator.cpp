#include "navigator.hpp"


std::filesystem::path Navigator::getWorkingDirectory(){
    return std::filesystem::current_path();
}

int Navigator::ChangeDir(std::string& path) {
    if (path == "~") setPathToHomeDirectory();
    else{
        std::filesystem::path newPath = path;
        if (!std::filesystem::exists(path)) return 1;
        std::filesystem::current_path(newPath);
        return 0;
    }

    return 0;
    
}

int Navigator::setPathToHomeDirectory()
{
    const char* homePath = std::getenv("HOME");
    std::filesystem::current_path(homePath);
    return 0;
}