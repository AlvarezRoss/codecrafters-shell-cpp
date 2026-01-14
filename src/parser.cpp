#include "parser.hpp"


Parser::Parser() {
    tokens.reserve(5);
}

std::string Parser::GetCommand(std::string& arg, char delimiter) {
    size_t begin = 0;
    size_t end = arg.find(delimiter);
    std::string command = arg.substr(begin,end);
    return command;
}

std::string Parser::GetFullArgumentString(std::string& arg, char delimiter) {
    size_t begin = arg.find(delimiter);
    //size_t end = arg.find(std::string::npos);
    std::string argumentString = arg.substr(begin+1,std::string::npos);
    return argumentString;
}

std::vector<std::string>* Parser::TokenizeFullCommand(std::string& command,char delimiter) {
    if (tokens.size() > 0) tokens.clear();
    size_t begin = 0;
    int argLen = command.length();
    for (int i = 0; i <= argLen; i++){
        if (command[i] == ' ' || i == argLen){
            std::string_view arg = command.substr(begin,i - begin);
            tokens.emplace_back(arg);
            begin = i + 1;
        }
    }
    return &tokens;
}
