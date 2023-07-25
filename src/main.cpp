#include <iostream>
#include "path.hpp"
#include "config.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "../../test/test_path/path");
    std::cout << path << std::endl;
    path = path::parentPath(path, 2);
    std::cout << path << std::endl;
    return 0;
}