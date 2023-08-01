#include <iostream>
#include "config.hpp"

int main()
{
    Config config;

    // add new key with the name "main key" with a value of "main val"
    config.addKeyValue("main key", "main val");

    // add new key with the name "dir" with a value of "my/path/to/file"
    config.addKeyValue("dir", "my/path/to/file");

    // add new section called "section 1"
    config.addSection("section 1");

    // add a new key called "secKey" with a value of "secVal" in "section 1"
    config.addKeyValue("section 1", "secKey", "secVal");
    
    // add more keys to "section 1"
    config.addKeyValue("section 1", "secKey2", "secVal2");
    config.addKeyValue("section 1", "secKey3", "secVal3");

    // modify the value of "secKey2" in "section 1" to "wassup"
    config.modifyKeyValue("section 1", "secKey2", "wassup");

    // modify the name of "secKey3" to "hello"
    config.modifyKeyName("section 1", "secKey3", "hello");

    // delete key "secKey" from "section 1"
    config.removeKey("section 1", "secKey");

    // add another section called "section 2"
    config.addSection("section 2");

    // add a key with no value to "section 2"
    config.addKey("section 2", "noval");

    // rename "section 2" to "new section"
    config.modifySectionName("section 2", "new section");

    // save to a file
    config.saveConfigToFile("config.txt");

    return 0;
}