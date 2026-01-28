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
    bool inSingleQuotes = false;
    bool inDoubleQuotes = false;
    std::string tok = "";
    tok.reserve(20);
    size_t begin = 0;
    int argLen = command.length();
    for (int i = 0; i <= argLen; i++){
        
        if (command[i] == '\'' && !inDoubleQuotes) {
            if (command[i+1] == '\'') {
                i++;
                continue;
            }   
            if (inSingleQuotes){
                std::string tok = std::string(command.data() + begin, i - begin);
                tok.erase(std::remove(tok.begin(),tok.end(),'\''),tok.end());
                tokens.emplace_back(tok);
            }
            begin = i + 1;
            inSingleQuotes = !inSingleQuotes;
        }
        if (command[i] == '\"') {
            if (command[i+1] == '\"'){
                i++;
                continue;
            }
            if (inDoubleQuotes) {
                std::string tok = std::string(command.data() + begin, i - begin);
                tok.erase(std::remove(tok.begin(),tok.end(),'\"'), tok.end());
                tokens.emplace_back(tok);
            }
            begin = i + 1;
            
            inDoubleQuotes = !inDoubleQuotes;
        }
        if (!inDoubleQuotes && !inSingleQuotes) {
                
                if (command[i] == delimiter || i >= argLen) {
                    if (command[i - 1] == delimiter || command[i - 1] == '\'' || command[i - 1] == '\"'){
                        begin = i + 1;
                        continue;
                    }
                    if (tok.find_first_not_of(' ') != std::string::npos) {
                        tokens.emplace_back(tok);
                        tok = "";
                        begin = i+1;
                    }
                    
                }
                if (command[i] == '\\') {
                    tok.append(1,command[i+1]);
                    if (i+2 >= argLen){
                        tokens.emplace_back(tok);
                        tok = "";
                        begin = i+1;
                    }
                    else {
                        i++;
                        begin = i+1;
                    }
                    continue;
                } 
                else if (command[i] != ' ' && command[i] != '\"' && command[i] != '\''){
                    tok.append(1,command[i]);
                    begin = i+1;
                    continue;
                } 
            begin = i+1;
                
        }

     }
    return &tokens;
}


