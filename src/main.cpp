#include <iostream>
#include "path.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    string source = path::sourcePath();
    path::copy(path::join(source, "Utility.exe"), path::join(source, "temp/sandbox/"));
    
    return 0;
}