#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
using namespace utility::path;
namespace out = utility::print;
namespace fs = std::filesystem;

int main()
{
    cout << find(sourcePath(), "any.txt", 1) << endl;
    cout << find(sourcePath(), "gg.txt", 1) << endl;
    cout << find(sourcePath(), "gg.txt", PathTraversal::Recursive) << endl;
    cout << find(currentPath(), "gg.txt", PathTraversal::Recursive) << endl;
    cout << find(currentPath(), "gg.txt", 3) << endl;

    out::print(findAll(currentPath(), "any.txt", PathTraversal::Recursive), '\n');
    out::print(findAll(currentPath(), "any.txt", 10), '\n');
    return 0;
}