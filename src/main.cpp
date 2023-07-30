#include <iostream>
#include "path.hpp"

int main()
{
    std::string from = path::joinPath(path::sourcePath(), "temp");
    std::string to = path::joinPath(path::sourcePath(), "temp/a/b/c");
    // std::filesystem::copy(from, to, std::filesystem::copy_options::recursive);
    path::copy(from, to);
    
    return 0;
}