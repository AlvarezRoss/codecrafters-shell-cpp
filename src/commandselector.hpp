#pragma once

#include <array>
#include <string_view>
#include <string>


enum class Command {
    exit,
    echo,
    type,
    pwd,
    cd,
    unkown
};

constexpr std::array<std::pair<std::string_view,Command>,5> commandTable {{
    {"exit",Command::exit},
    {"echo",Command::echo},
    {"type",Command::type},
    {"pwd",Command::pwd},
    {"cd",Command::cd}
}
};

Command GetSelectedCommand(std::string& input);