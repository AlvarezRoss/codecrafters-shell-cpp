#pragma once
#include <string>
#include <filesystem>
#include <vector>

class Executer {
    private:
        const char* pathVariable;
        char* executable;
        std::vector<std::filesystem::path> exeFiles;

    public:
        Executer();
        std::filesystem::path FindExe(std::string& name);
        void Execute(std::filesystem::path exePath);
};