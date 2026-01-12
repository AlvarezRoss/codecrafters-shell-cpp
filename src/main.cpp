#include <iostream>
#include <string>
#include "parser.hpp"
#include "commandselector.hpp"

void HandleBaseCommand(std::string cmdArg, Parser* parser);

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

void HandleBaseCommand(std::string cmdArg, Parser* parser) {
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
  case Command::unkown:
    std::cout<<command<<": command not found\n";
  default:
    break;
  }

  return;
}
