#include <iostream>
#include <string>
#include "parser.hpp"
#include "commandselector.hpp"
#include "executer.hpp"


void HandleBaseCommand(std::string& cmdArg, Parser* parser);
void HandleTypeCommand(std::string& cmdArg, Parser* parser);
int HandleExecuteCommand(std::string& cmdArg, Parser* parser);

int main() {
  
  std::string cmd;
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  Parser* parser = new Parser();
  while(true) {
    std::cout<<"$ ";
    std::getline(std::cin,cmd);
    HandleBaseCommand(cmd,parser);
  }
  delete parser;
  return 0;
}

void HandleBaseCommand(std::string& cmdArg, Parser* parser) {
  std::string command = parser->GetCommand(cmdArg,' ');
  switch (GetSelectedCommand(command))
  {
  case Command::exit:
    delete parser;
    std::exit(0);
    break;
  case Command::echo: {
    std::string toPrint = parser->GetFullArgumentString(cmdArg,' ');
    std::cout<<toPrint<<"\n";
    break;
    }
  case Command::type: {
    HandleTypeCommand(cmdArg,parser);
    break;
  }
  case Command::unkown: {
    int ExecuteStatus = HandleExecuteCommand(cmdArg,parser);
    if(ExecuteStatus != 0) {
      std::cout<<command<<": command not found\n";
    }
    break;
    }
  default:
    break;
  }

  return;
}

void HandleTypeCommand(std::string& cmdArg, Parser* parser) {
  std::string arg = parser->GetFullArgumentString(cmdArg,' ');
    Command commandType = GetSelectedCommand(arg);
    if (commandType != Command::unkown) std::cout<<arg<<" is a shell builtin\n";
    else {
      Executer* executer = new Executer();
      std::filesystem::path exePath = executer->FindExe(arg);
      if (exePath.empty()){
        std::cout<<arg<<": not found\n";
      }
      else {
        std::cout<<arg<< " is "<< exePath.string()<<"\n";
      }
      delete executer;
    }
    return;
}

int HandleExecuteCommand(std::string& cmdArg, Parser* parser) {
  std::vector<std::string>* toks = parser->TokenizeFullCommand(cmdArg,' ');
  std::string exeName = parser->GetCommand(cmdArg,' ');
  Executer* executer = new Executer();
  std::filesystem::path exePath = executer->FindExe(exeName);
  if (exePath.empty()) return 1;
  if (executer->Execute(exePath,(*toks)) != 0) return 2;
  delete executer;
  return 0;
}
