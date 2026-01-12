#pragma once

#include <array>
#include <string_view>
#include <string>


enum class Command {
    exit,
    echo,
    unkown
};

constexpr std::array<std::pair<std::string_view,Command>,3> commandTable {{
    {"exit",Command::exit},
    {"echo",Command::echo}
}
};

Command GetSelectedCommand(std::string& input);