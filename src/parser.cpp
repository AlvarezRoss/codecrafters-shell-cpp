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
// Tokenizer supports ' and '\' on command lines  
std::vector<std::string>* Parser::TokenizeFullCommand(std::string& command,char delimiter) {
    if (tokens.size() > 0) tokens.clear();
    bool inSingleQuotes = false;
    bool inDoubleQuotes = false;
    std::string word = ""; // strings used to append chars when not inside quotes
    word.reserve(50);
    size_t begin = 0;
    int argLen = command.length();
    for (int i = 0; i <= argLen; i++){
        
        if (command[i] == '\'' && !inDoubleQuotes) {// skips contiguous single quotes
            if (command[i+1] == '\'') {
                i++;
                continue;
            }   

            if (inSingleQuotes){
                std::string tok = std::string(command.data() + begin, i - begin); // Creates a string from the command and the begin and i delimiters
                tok.erase(std::remove(tok.begin(),tok.end(),'\''),tok.end()); // removes any single quotes from the string
                if (word != "") {
                    word.append(tok);
                    tokens.emplace_back(word);
                    word = "";
                }
                else {
                    tokens.emplace_back(tok);
                    word = "";
                }
            }
            begin = i + 1;
            inSingleQuotes = !inSingleQuotes;
        }
        if (command[i] == '\"' && !inSingleQuotes) {
            
            if (command[i+1] == '\"'){ // skips over contiguous double quotes
                i++;
                continue;
            }
            if (i + 1 >= argLen || command[i+1] == ' '){
                tokens.emplace_back(word);
                word = "";
            }
            inDoubleQuotes = !inDoubleQuotes;
            begin = i + 1; // begin in incremented to make sure single quote handle is correct
            i++; //skips the " when encountered

        }
        if (inDoubleQuotes) {
                if (command[i] == '\\') { // if a \ is found it appends the next char
                        if (command[i+1] == '\"' || command[i+1] == '\\'){
                            word.append(1,command[i+1]);
                            i++;
                            continue;
                        } else {
                            word.append(1, command[i]);
                        }
                    }
                else{
                    word.append(1,command[i]);
                    continue;
                } 
                
            }
        if (!inDoubleQuotes && !inSingleQuotes) {
                
                if (command[i] == delimiter || i >= argLen) {
                    //Adds whole string to vector if a delimiter is reached
                    if (command[i - 1] == delimiter || command[i - 1] == '\'' || command[i - 1] == '\"'){
                        begin = i + 1;
                        continue;
                    }
                    if (word.find_first_not_of(' ') != std::string::npos) {
                        tokens.emplace_back(word);
                        word = "";
                        begin = i+1;
                    }
                    
                }
                if (command[i] == '\\') {
                    word.append(1,command[i+1]);
                    if (i+2 >= argLen){
                        tokens.emplace_back(word);
                        word = "";
                        begin = i+1;
                    }
                    else {
                        i++;
                    }
                    continue;
                } 
                else if (command[i] != ' ' && command[i] != '\"' && command[i] != '\''){
                    word.append(1,command[i]);
                    continue;
                } 
                
        }

     }
    return &tokens;
}


