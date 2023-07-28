#include <iostream>
#include "path.hpp"
#include "config.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "../../test/test_path/config/config.txt");
    Config config;

    config.addKeyValue("main", "main value");

    config.addSection("section 1");
    config.addKeyValue("section 1", "key 1", "hello");
    config.addKeyValue("section 1", "key2", "world");

    config.addSection("section 2");
    config.addKeyValue("section 2", "key1", "some value");
    config.addKeyValue("section 2", "key2", "some value");
    
    config.saveConfigToFile("test.txt");
    
    return 0;
}