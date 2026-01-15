#include "navigator.hpp"


std::filesystem::path Navigator::getWorkingDirectory(){
    return std::filesystem::current_path();
}

int Navigator::ChangeDir(std::string& path) {
    std::filesystem::path newPath = path;
    if (!std::filesystem::exists(path)) return 1;
    std::filesystem::current_path(newPath);
    return 0;
}