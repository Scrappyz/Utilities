#include <iostream>
#include "utility.hpp"

namespace mathUtil = utility::math;

int main()
{
    double a = 1.125986;
    double b = 1.123698944;
    std::cout << a << " + " << b << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << mathUtil::precision(a, 2) << " + " << mathUtil::precision(b, 2) << std::endl;
    std::cout << (mathUtil::precision(a, 2) == mathUtil::precision(b, 2)) << std::endl;
    std::cout << mathUtil::precision(30.36, 4) << std::endl;

    return 0;
}