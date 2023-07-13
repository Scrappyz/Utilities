#include <iostream>
#include "path.hpp"
#include "config.hpp"

using namespace std;

int main()
{
    std::string config_path = path::join(path::sourcePath(), "config.txt");
    Config config(config_path);
    std::cout << config.getValueOf("key1") << std::endl;
    std::cout << config.getValueOf("Section 1", "key2") << std::endl;
    std::cout << config.getValueOf("Section 2", "key 3") << std::endl;
    std::cout << config.getValueOf("Section 2", "key4") << std::endl;
}