#include <iostream>
#include <string>
#include "parser.hpp"
#include "commandselector.hpp"
#include "executer.hpp"
#include "navigator.hpp"


void HandleBaseCommand(std::string& cmdArg, Parser* parser, Navigator* navigator);
void HandleTypeCommand(std::string& cmdArg, Parser* parser);
int HandleExecuteCommand(std::string& cmdArg, Parser* parser);

int main() {
  
  std::string cmd;
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  Parser* parser = new Parser();
  Navigator* navigator = new Navigator();
  while(true) {
    std::cout<<"$ ";
    std::getline(std::cin,cmd);
    HandleBaseCommand(cmd,parser,navigator);
  }
  delete parser;
  delete navigator;
  return 0;
}

void HandleBaseCommand(std::string& cmdArg, Parser* parser, Navigator* navigator) {
  std::string command = parser->GetCommand(cmdArg,' ');
  std::string argString = parser->GetFullArgumentString(cmdArg,' ');
  switch (GetSelectedCommand(command))
  {
  case Command::exit:
    delete parser;
    delete navigator;
    std::exit(0);
    break;
  case Command::echo: {
    //std::string toPrint = parser->GetFullArgumentString(cmdArg,' ');
    //std::cout<<toPrint<<"\n";
    std::vector<std::string>* toPirnt = parser->TokenizeFullCommand(argString,' ');
    for (const auto& element : (*toPirnt)) std::cout<<element<<" ";
    std::cout<<std::endl;
    break;
    }
  case Command::type: {
    HandleTypeCommand(cmdArg,parser);
    break;
  }
  case Command::pwd: {
    std::cout<<navigator->getWorkingDirectory().string()<<"\n";
    break;
  }
  case Command::cd: {
    std::string pathString = parser->GetFullArgumentString(cmdArg,' ');
    if (navigator->ChangeDir(pathString) != 0) std::cout<<"cd: "<<pathString<<": No such file or directory\n";
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
  Executer* executer = new Executer();
  std::filesystem::path exePath = executer->FindExe((*toks)[0]);
  if (exePath.empty()) return 1;
  if (executer->Execute(exePath,(*toks)) != 0) return 2;
  delete executer;
  return 0;
}
