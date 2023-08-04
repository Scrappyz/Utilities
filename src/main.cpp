#include <iostream>
#include "path.hpp"

int main()
{
    std::string p1 = path::joinPath(path::sourcePath(), "../../test/test_path/path/sandbox/srcs.jpg");
    std::string p2 = path::joinPath(path::sourcePath(), "../../test/test_path/path/new/srcs.jpg");

    std::cout << path::hasSameContent(p1, p2);

    return 0;
}