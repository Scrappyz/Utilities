#include "config.hpp"
#include "path.hpp"
#include "gtest/gtest.h"

std::string test_path = path::joinPath(path::sourcePath(), "../test_path/config");
std::string config_path = path::joinPath(test_path, "config.txt");

class ConfigTest : public Config {
    public:
        ConfigTest() : Config() {}
        ConfigTest(const std::string& config_path) : Config(config_path) {}

        const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getConfig() const
        {
            return config;
        }
};

std::vector<std::string> getFileContent(const std::string& path)
{
    std::vector<std::string> v;
    std::ifstream file(path);

    if(!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    std::string line;
    while(getline(file, line)) {
        while(line.back() == ' ') {
            line.pop_back();
        }

        if(line.empty()) {
            v.push_back(line);
            continue;
        }

        std::string temp;

        int i = 0;
        while(i < line.size() && line[i] == ' ') { // skip whitespaces
            i++;
        }

        if(line[i] == '#') { // is a comment
            continue;
        }

        while(i < line.size() && line[i] != '#') {
            temp.push_back(line[i]);
            i++;
        }

        v.push_back(temp);
    }

    return v;
}

TEST(constructor, empty_section_is_available_on_initialization)
{
    ConfigTest config;
    config.addKey("new key");
    EXPECT_THROW(config.addKey("section 1", "new key"), std::exception);
    EXPECT_EQ(config.doesKeyExist("new key"), true);
    
    ConfigTest config1(config_path);
    config1.addKey("new key");
    EXPECT_EQ(config.doesKeyExist("new key"), true);
}

TEST(setConfig, general)
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> expected_config = {
        {"", std::unordered_map<std::string, std::string>({{"key1", "val1"}, {"key2", "val2"}, {"key 3", "val3"}, {"key4", "val 4"}, {"key 5", "val 5"}})},
        {"Section 1", std::unordered_map<std::string, std::string>({{"key1", "val1"}, {"key2", "val2"}, {"key 3", "val3"}, {"key4", "val 4"}, {"key 5", "val 5"}})},
        {"Section 2", std::unordered_map<std::string, std::string>({{"key1", "val1"}, {"key2", "val2"}, {"key 3", "val3"}, {"key4", "val 4"}, {"key 5", "val 5"}})}
    };
    ConfigTest config(config_path);

    EXPECT_EQ(config.getConfig(), expected_config);
}

TEST(saveConfigToFile, general)
{
    ConfigTest config(config_path);
    config.removeKey("key1");
    config.removeKey("Section 1", "key1");
    config.removeKey("Section 2", "key1");
    config.modifyKeyName("key 3", "forger");
    config.modifyKeyValue("forger", "sword");
    config.modifyKeyName("Section 1", "key 3", "mario bros");
    config.modifyKeyValue("Section 1", "mario bros", "mario & luigi");

    config.saveConfigToFile(path::joinPath(test_path, "actual.txt"));

    ConfigTest expected_config(path::joinPath(test_path, "expected.txt"));
    ConfigTest actual_config(path::joinPath(test_path, "actual.txt"));
    EXPECT_EQ(expected_config, actual_config);
}

TEST(getValue, general)
{
    ConfigTest config(config_path);

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

TEST(getValue, errors)
{
    ConfigTest config;
    EXPECT_THROW(config.getValue("hello"), std::exception);
    EXPECT_THROW(config.getValue("hello", 5), std::exception);
    EXPECT_EQ(config.getValue("hello", false), "");
    EXPECT_EQ(config.getValue("hello", -5), "");

    config.addKeyValue("hello", "hi");
    EXPECT_EQ(config.getValue("hello"), "hi");
    EXPECT_EQ(config.getValue("hello", 5), "hi");
    EXPECT_EQ(config.getValue("hello", false), "hi");
    EXPECT_EQ(config.getValue("hello", -5), "hi");

    EXPECT_THROW(config.getValue("section", "hello"), std::exception);
    EXPECT_THROW(config.getValue("section", "hello", 3), std::exception);
    EXPECT_EQ(config.getValue("section", "hello", false), "");
    EXPECT_EQ(config.getValue("section", "hello", -3), "");
}

TEST(addSection, general)
{
    ConfigTest config(config_path);

    EXPECT_EQ(config.doesSectionExist("bobo"), false);
    config.addSection("bobo");
    EXPECT_EQ(config.doesSectionExist("bobo"), true);
}

TEST(addKey, general)
{
    ConfigTest config(config_path);

    EXPECT_EQ(config.doesKeyExist("poo"), false);
    config.addKey("poo");
    EXPECT_EQ(config.doesKeyExist("poo"), true);

    EXPECT_EQ(config.doesKeyExist("Section 1", "poo"), false);
    config.addKey("Section 1", "poo");
    EXPECT_EQ(config.doesKeyExist("Section 1", "poo"), true);
}

TEST(addKeyValue, general)
{
    ConfigTest config(config_path);

    EXPECT_EQ(config.doesKeyExist("poo") && config.doesKeyHaveValue("poo"), false);
    config.addKeyValue("poo", "amp");
    EXPECT_EQ(config.doesKeyExist("poo") && config.doesKeyHaveValue("poo"), true);

    EXPECT_EQ(config.doesKeyExist("Section 1", "poo") && config.doesKeyHaveValue("Section 1", "poo"), false);
    config.addKeyValue("Section 1", "poo", "amp");
    EXPECT_EQ(config.doesKeyExist("Section 1", "poo") && config.doesKeyHaveValue("Section 1", "poo"), true);
}

TEST(removeSection, general)
{
    ConfigTest config(config_path);

    EXPECT_EQ(config.doesSectionExist("Seggs"), false);
    config.addSection("Seggs");
    EXPECT_EQ(config.doesSectionExist("Seggs"), true);

    EXPECT_EQ(config.doesKeyExist("Seggs", "phonk") && config.doesKeyHaveValue("Seggs", "phonk"), false);
    config.addKeyValue("Seggs", "phonk", "cool");
    EXPECT_EQ(config.doesKeyExist("Seggs", "phonk") && config.doesKeyHaveValue("Seggs", "phonk"), true);
}

TEST(removeKey, general)
{
    ConfigTest config(config_path);

    config.addSection("Seggs");
    config.addKeyValue("Seggs", "ex", "shit");
    EXPECT_EQ(config.doesKeyExist("Seggs", "ex"), true);
    config.removeKey("Seggs", "ex");
    EXPECT_EQ(config.doesKeyExist("Seggs", "ex"), false);
}

TEST(modifySectionName, general)
{
    ConfigTest config(config_path);

    config.addSection("Seggs");
    EXPECT_EQ(config.doesSectionExist("Seggs") && !config.doesSectionExist("axe"), true);
    config.modifySectionName("Seggs", "axe");
    EXPECT_EQ(config.doesSectionExist("axe") && !config.doesSectionExist("Seggs"), true);
}

TEST(modifyKeyName, general)
{
    ConfigTest config(config_path);

    config.addKey("Barbie");
    EXPECT_EQ(config.doesKeyExist("Barbie") && !config.doesKeyExist("Ken"), true);
    config.modifyKeyName("Barbie", "Ken");
    EXPECT_EQ(config.doesKeyExist("Ken") && !config.doesKeyExist("Barbie"), true);
}

TEST(modifyKeyValue, general)
{
    ConfigTest config(config_path);

    config.addKeyValue("Oppenheimer", "Nuke");
    EXPECT_EQ(config.getValue("Oppenheimer"), "Nuke");
    config.modifyKeyValue("Oppenheimer", "BOOM");
    EXPECT_EQ(config.getValue("Oppenheimer"), "BOOM");
}