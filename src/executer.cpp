#include "executer.hpp"

Executer::Executer() {
    pathVariable = std::getenv("PATH");
    exeFiles.reserve(40);

    std::string pathEnvionrment(pathVariable ? pathVariable:""); // converts c string to c++ string
    pathEnvionrment.append(":"); // used to have the same delimiter on all paths including the last one

    size_t begin = 0;
    for (int i = 0; i < pathEnvionrment.length(); i++)
    {
        if (pathEnvionrment[i] == ':') {
            std::string_view path = pathEnvionrment.substr(begin, i - begin);
            if (std::filesystem::exists(path)) {
                for (const auto & entry : std::filesystem::directory_iterator(path)) {
                    // & is used for the AND operator since permissions() returns a bitmask of permissions
                    if (!entry.is_directory() && (entry.status().permissions() & std::filesystem::perms::owner_exec) == std::filesystem::perms::owner_exec) {
                        exeFiles.emplace_back(entry);
                    }
                }
            }
            begin = i + 1;
        }
    }
   

}

std::filesystem::path Executer::FindExe(std::string& name) {
   
    for (const auto& entry : exeFiles) {
        if (entry.stem().string() == name) {
            return entry;
        }
    }

    return std::filesystem::path {}; // return empty path.
}

int Executer::Execute(std::filesystem::path exePath, std::vector<std::string>& args) {
    std::vector<char*>cstrs;
    size_t argsLen = args.size();
    cstrs.reserve(argsLen);
    for (size_t i = 0; i < argsLen ; i++) {
        cstrs.emplace_back(const_cast<char*>(args[i].c_str()));
    }
    cstrs.emplace_back(nullptr);
    // Forms the proccess and if we are in the child process childId == 0 then execute the new program
    pid_t id = fork();
    if (id == 0){
        if (execvp(exePath.c_str(),cstrs.data()) != 0) return 1;
    }
    if (id != 0) wait(NULL);

    return 0;
    
}