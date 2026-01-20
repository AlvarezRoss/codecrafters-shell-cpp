#include "parser.hpp"
#include <iostream>

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
    std::string argumentString = arg.substr(begin+1,std::string::npos);
    return argumentString;
}
// Tokenizer supports ' on command lines
std::vector<std::string>* Parser::TokenizeFullCommand(std::string& command,char delimiter) {
    if (tokens.size() > 0) tokens.clear();
    size_t begin = 0;
    int argLen = command.length();
    for (int i = 0; i <= argLen; i++){
        if (command[i] == '\'') {
            if (command[i+1] == '\''){// if there are empty quotes adds to tokens vector the word before the first quote
                std::string_view wordBeforeQuote = std::string_view(command.data() + begin, i - begin);
                tokens.emplace_back(wordBeforeQuote);
                begin = i + 1;
                continue;
            }
            begin = i+1;
            for (int g = begin; g < argLen; g++) { // Adds to vector word between quotes
                if (command[g] == '\'') {
                    std::string_view quotedCommand = std::string_view(command.data() + begin, g - begin);
                    tokens.emplace_back(quotedCommand);                    
                    i = g+1;
                    begin = i;                  
                }
            }
        }
        if (command[i] == delimiter|| i == argLen){
            if (command[i-1] != delimiter) {
                std::string_view arg = std::string_view(command.data() + begin, i-begin);
                tokens.emplace_back(arg);
                if (i + 1 < argLen) {
                    std::string_view spaceChar = std::string_view(command.data() + i, 1);
                    tokens.emplace_back(spaceChar); // Adds one space to the vector after every word that is not between quotes
                }
                begin = i + 1;
            }
            else {
                begin++;
                continue;
            }           
        }
    }
    return &tokens;
}

