#include <iostream>
#include "path.hpp"

using namespace std;
namespace fs = std::filesystem;

string joinPathString(const fs::path& p1, const fs::path& p2)
{
    return fs::weakly_canonical(p1 / p2).string();
}

int main()
{
    string source = path::sourcePath();
    return 0;
}