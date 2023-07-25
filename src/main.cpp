#include <iostream>
#include "path.hpp"
#include "config.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "../../test/test_path/config/config.txt");
    Config config(path);
    config.setConfigToFile(path::currentPath() + "/template.txt");
    
    return 0;
}