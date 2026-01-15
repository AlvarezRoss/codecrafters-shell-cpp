#pragma once

#include <filesystem>

class Navigator {
    public:
        std::filesystem::path getWorkingDirectory();
        int ChangeDir(std::string& path);
};