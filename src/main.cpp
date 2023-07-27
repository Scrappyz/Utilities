#include <iostream>
#include "path.hpp"
#include "config.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "../../test/test_path/config/config.txt");
    Config config(path);
    
    config.addKeyValue("new key", "new value");
    std::cout << config.getValue("new key") << std::endl;
    config.modifyKeyValue("new key", "cool value");
    std::cout << config.getValue("new key") << std::endl;
    
    return 0;
}