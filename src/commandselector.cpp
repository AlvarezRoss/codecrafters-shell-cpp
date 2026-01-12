#include "commandselector.hpp"



Command GetSelectedCommand(std::string& input) {
    std::string_view in = input;
    for (auto& [name,cmd]:commandTable) {
        if (name == input) return cmd;
    }
    return Command::unkown;
}
