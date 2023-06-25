#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isAbsolutePath("bin/debug") << endl;
    cout << path::isAbsolutePath("D:/bin/debug") << endl;
    return 0;
}