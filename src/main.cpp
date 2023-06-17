#include <iostream>
#include "path.hpp"

using namespace std;
using namespace utility::path;
namespace fs = std::filesystem;

int main()
{
    cout << joinPath({"a/b/c/d/.."}) << endl;
    return 0;
}