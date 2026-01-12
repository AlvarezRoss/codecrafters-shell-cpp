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
    size_t end = arg.find(std::string::npos);
    std::string argumentString = arg.substr(begin+1,end);
    return argumentString;
}
