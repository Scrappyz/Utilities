#include <iostream>
#include "path.hpp"

using namespace std;
namespace path = utility::path;
namespace fs = std::filesystem;

string joinPathString(const fs::path& p1, const fs::path& p2)
{
    return fs::weakly_canonical(p1 / p2).string();
}

int main()
{
    string source = path::sourcePath();
    path::copy(path::joinPath(source, "boes"), path::joinPath(source, "fold/"));
    return 0;
}