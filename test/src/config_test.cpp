#include "config.hpp"
#include "path.hpp"
#include "gtest/gtest.h"

std::string test_path = path::joinPath(path::sourcePath(), "../test_path/config");

TEST(getValue, general)
{
    std::string config_path = path::joinPath(test_path, "config.txt");
    Config config(config_path);

    EXPECT_EQ(config.getValue("key1"), "val1");
    EXPECT_EQ(config.getValue("key2"), "val2");
    EXPECT_EQ(config.getValue("key 3"), "val3");
    EXPECT_EQ(config.getValue("key4"), "val 4");
    EXPECT_EQ(config.getValue("key 5"), "val 5");

    EXPECT_EQ(config.getValue("Section 1", "key1"), "val1");
    EXPECT_EQ(config.getValue("Section 1", "key2"), "val2");
    EXPECT_EQ(config.getValue("Section 1", "key 3"), "val3");
    EXPECT_EQ(config.getValue("Section 1", "key4"), "val 4");
    EXPECT_EQ(config.getValue("Section 1", "key 5"), "val 5");

    EXPECT_EQ(config.getValue("Section 2", "key1"), "val1");
    EXPECT_EQ(config.getValue("Section 2", "key2"), "val2");
    EXPECT_EQ(config.getValue("Section 2", "key 3"), "val3");
    EXPECT_EQ(config.getValue("Section 2", "key4"), "val 4");
    EXPECT_EQ(config.getValue("Section 2", "key 5"), "val 5");

}

TEST(modifyValueInFile, general)
{
    std::string config_path = path::joinPath(test_path, "test.txt");
}