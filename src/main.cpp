#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
namespace out = utility::print;

int main(int argc, char* argv[])
{
    path::open("CMakeLists.txt");
    
    return 0;
}