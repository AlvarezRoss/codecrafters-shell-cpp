#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include <bits/stdc++.h> 

class Executer {
    private:
        const char* pathVariable;
        char* executable;
        std::vector<std::filesystem::path> exeFiles;

    public:
        Executer();
        std::filesystem::path FindExe(std::string& name);
        int Execute(std::filesystem::path exePath, std::vector<std::string>& args);
};