#pragma once

#include <string>
#include <vector>


    class Parser{
        private:
            std::vector<std::string> tokens;
        public:
            Parser();
            std::string GetCommand(std::string& arg,char delimiter);
            std::string GetFullArgumentString(std::string& arg,char delimiter);
    };

