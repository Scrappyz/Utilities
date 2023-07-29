#include <iostream>
#include "path.hpp"

int main()
{
    std::string from = path::joinPath(path::sourcePath(), "stuff/");
    std::string to = path::joinPath(path::sourcePath(), "temp");
    path::copy(from, to);
    
    return 0;
}