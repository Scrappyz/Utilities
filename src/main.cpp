#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
namespace path = utility::path;
namespace out = utility::print;
namespace fs = std::filesystem;

string joinPathString(const fs::path& p1, const fs::path& p2)
{
    return fs::weakly_canonical(p1 / p2).string();
}

int main()
{
    string source = path::sourcePath();
    path::move(path::joinPath(source, "temp/"), path::joinPath(source, "sandbox"));
    return 0;
}