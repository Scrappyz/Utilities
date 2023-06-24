#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
namespace path = utility::path;
namespace out = utility::print;
namespace fs = std::filesystem;

int main()
{
    path::copy(path::joinPath(path::sourcePath(), "temp/any.txt"), path::sourcePath(), path::CopyOption::OverwriteExisting);
    return 0;
}