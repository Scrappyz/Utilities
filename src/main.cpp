#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    path::move("sandbox", "temp", path::CopyOption::OverwriteDirectory);
    
    return 0;
}