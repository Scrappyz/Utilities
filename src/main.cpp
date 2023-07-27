#include <iostream>
#include "path.hpp"
#include "config.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "../../test/test_path/config/config.txt");
    Config config(path);
    
    std::cout << config.doesSectionExist("new section") << std::endl;
    config.addSection("new section");
    std::cout << config.doesSectionExist("new section") << std::endl;
    return 0;
}