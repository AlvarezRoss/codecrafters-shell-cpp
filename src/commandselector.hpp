#pragma once

#include <array>
#include <string_view>
#include <string>


enum class Command {
    exit,
    echo,
    type,
    pwd,
    unkown
};

constexpr std::array<std::pair<std::string_view,Command>,4> commandTable {{
    {"exit",Command::exit},
    {"echo",Command::echo},
    {"type",Command::type},
    {"pwd",Command::pwd}
}
};

Command GetSelectedCommand(std::string& input);