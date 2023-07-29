#include <iostream>
#include "path.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "test");
    path::remove(path);
    
    return 0;
}