#include <iostream>
#include "path.hpp"
#include "config.hpp"

using namespace std;

int main()
{
    path::copy(path::join(path::sourcePath(), "temp/test.txt"), path::join(path::sourcePath(), "config.txt"), path::CopyOption::OverwriteExisting);
    std::string config_path = path::join(path::sourcePath(), "config.txt");
    std::cout << Config::modifyValueInFile(config_path, "key1", "cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "key 3", "cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "key g3", "cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "Section 1", "key4", "my cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "Section 1", "key 5", "my cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "Section 2", "key 5", "cookie monster") << std::endl;

    return 0;
}