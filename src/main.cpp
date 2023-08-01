#include <iostream>
#include "config.hpp"

int main()
{
    Config config;
    std::cout << config.doesSectionHaveKeys() << std::endl; // no keys
    config.addKey("key1"); // add a key called "key1"
    std::cout << config.doesSectionHaveKeys() << std::endl; // now has keys

    config.addSection("section"); // add new section called "section"
    std::cout << config.doesSectionHaveKeys("section") << std::endl; // no keys
    config.addKey("section", "new key"); // add new key to "section"
    std::cout << config.doesSectionHaveKeys("section") << std::endl; // now has keys
    
    return 0;
}