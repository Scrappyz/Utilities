#include "config.hpp"
#include "path.hpp"
#include "gtest/gtest.h"

std::string test_path = path::joinPath(path::sourcePath(), "../test_path/config");
std::string config_path = path::joinPath(test_path, "config.txt");

TEST(setConfig, general)
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> expected_config = {
        {"", std::unordered_map<std::string, std::string>({{"key1", "val1"}, {"key2", "val2"}, {"key 3", "val3"}, {"key4", "val 4"}, {"key 5", "val 5"}})},
        {"Section 1", std::unordered_map<std::string, std::string>({{"key1", "val1"}, {"key2", "val2"}, {"key 3", "val3"}, {"key4", "val 4"}, {"key 5", "val 5"}})},
        {"Section 2", std::unordered_map<std::string, std::string>({{"key1", "val1"}, {"key2", "val2"}, {"key 3", "val3"}, {"key4", "val 4"}, {"key 5", "val 5"}})}
    };
    Config config(config_path);

    EXPECT_EQ(config.getConfig(), expected_config);
}

TEST(getValue, general)
{
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

TEST(addSection, general)
{
    Config config(config_path);

    EXPECT_EQ(config.doesSectionExist("bobo"), false);
    config.addSection("bobo");
    EXPECT_EQ(config.doesSectionExist("bobo"), true);
}

TEST(addKey, general)
{
    Config config(config_path);

    EXPECT_EQ(config.doesKeyExist("poo"), false);
    config.addKey("poo");
    EXPECT_EQ(config.doesKeyExist("poo"), true);

    EXPECT_EQ(config.doesKeyExist("Section 1", "poo"), false);
    config.addKey("Section 1", "poo");
    EXPECT_EQ(config.doesKeyExist("Section 1", "poo"), true);
}

TEST(addKeyValue, general)
{
    Config config(config_path);

    EXPECT_EQ(config.doesKeyExist("poo") && config.doesKeyHaveValue("poo"), false);
    config.addKeyValue("poo", "amp");
    EXPECT_EQ(config.doesKeyExist("poo") && config.doesKeyHaveValue("poo"), true);

    EXPECT_EQ(config.doesKeyExist("Section 1", "poo") && config.doesKeyHaveValue("Section 1", "poo"), false);
    config.addKeyValue("Section 1", "poo", "amp");
    EXPECT_EQ(config.doesKeyExist("Section 1", "poo") && config.doesKeyHaveValue("Section 1", "poo"), true);
}

