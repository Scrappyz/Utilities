#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isFile("bin/Debug/temp/test.txt") << endl; // exists
    cout << path::isFile("bin/Debug/temp/tt.txt") << endl; // not exists
    cout << path::isFile("bin/Debug") << endl; // not a file

    return 0;
}