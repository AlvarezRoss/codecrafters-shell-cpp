#pragma once

#include <string>
#include <vector>


    class Parser{
        public:
            Parser();
            std::string GetCommand(std::string& arg,char delimiter);
            std::string GetFullArgumentString(std::string& arg,char delimiter);
            std::vector<std::string>* TokenizeFullCommand(std::string& command, char delimiter);
            std::vector<std::string> tokens;
    };

