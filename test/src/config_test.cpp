#include "config.hpp"
#include "path.hpp"
#include "gtest/gtest.h"

std::string test_path = path::joinPath(path::sourcePath(), "../test_path/config");

TEST(getValueOf, general)
{
    
}