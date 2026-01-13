#pragma once

#include <array>
#include <string_view>
#include <string>


enum class Command {
    exit,
    echo,
    type,
    unkown
};

constexpr std::array<std::pair<std::string_view,Command>,3> commandTable {{
    {"exit",Command::exit},
    {"echo",Command::echo},
    {"type",Command::type}
}
};

Command GetSelectedCommand(std::string& input);