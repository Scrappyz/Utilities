#include <iostream>
#include "path.hpp"

int main()
{
    std::string from = path::joinPath(path::sourcePath(), "./");
    std::string to = path::joinPath(path::sourcePath(), "a/b/c");
    path::copy(from, to);
    
    return 0;
}