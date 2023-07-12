#include <iostream>
#include "path.hpp"
#include "config.hpp"

using namespace std;

void printConfig(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& keyval)
{
    for(const auto& i : keyval) {
        std::cout << "[" << i.first << "]" << std::endl;
        for(const auto& j : i.second) {
            std::cout << "    " << j.first << " = " << j.second << std::endl;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    string source = path::sourcePath();
    path::copy(path::join(source, "sandbox/"), path::join(source, "temp"), path::CopyOption::OverwriteAll);
    return 0;
}