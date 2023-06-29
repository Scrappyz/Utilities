#include "cli.hpp"
#include <typeinfo>
#include <gtest/gtest.h>

using namespace std;

TEST(setArguments, testAll)
{
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "origin", "-h", "-o"});
    unordered_set<string> expected_sub = {""};
    EXPECT_EQ(cli.getValidSubcommands(), expected_sub);
    EXPECT_EQ(cli.getActiveSubcommand(), "");
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 0);
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 0);
    cli.setValidSubcommands({"remote", "add", "origin"});
    EXPECT_EQ(cli.getActiveSubcommand(), "remote");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 1);
    EXPECT_EQ(cli.getActiveSubcommand(), "remote");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 1);
    cli.setValidSubcommands({"remote", "remote add origin"});
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add origin");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 3);

    cli.setValidSubcommands({"add", "origin", "remote add origin"});
    cli.setArguments({"MyProgram", "add", "origin"});
    EXPECT_EQ(cli.getActiveSubcommand(), "add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 1);

    cli.setValidSubcommands({"add", "origin", "remote add origin"});
    cli.setArguments({"MyProgram", "remote", "add", "origin"});
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add origin");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 3);

    cli.setArguments({"MyProgram", "add", "hi"});
    EXPECT_EQ(cli.getActiveSubcommand(), "add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 1);
    cli.setValidSubcommands({"add", "hi"});
    EXPECT_EQ(cli.getActiveSubcommand(), "add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 1);

    cli.setValidSubcommands({""});
    EXPECT_EQ(cli.getActiveSubcommand(), "");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 0);

    cli.setArguments({"MyProgram", "remote", "-h"});
    cli.setValidSubcommands({"remote", "remote add"});
    cli.setValidFlags("remote", {"-h"});
    cli.setValidFlags("remote add", {"--help"});
    EXPECT_EQ(cli.getActiveSubcommand(), "remote");
    EXPECT_EQ(cli.isFlagSet("-h"), true);
    cli.setArguments({"MyProgram", "remote", "add", "--help"});
    EXPECT_EQ(cli.isFlagSet("remote", "-h"), false);
    EXPECT_EQ(cli.isFlagSet("--help"), true);
}

TEST(setValidSubcommands, testing)
{
    CLI cli({"MyProgram", "remote", "add", "--origin"});
    cli.setValidSubcommands({"pull", "push", "remote add"});
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 2);

    cli.setValidSubcommands({"", ""});
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 0);

    cli.setValidSubcommands({"", "  hello", "   hi   ", "boi   "});
    unordered_set<string> expected_subcmd = {"", "hello", "hi", "boi"};
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 1);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subcmd);

    CLI cmd({"MyProgram"});
    expected_subcmd = {""};
    cmd.setValidSubcommands({});
    EXPECT_EQ(cmd.getValidSubcommands(), expected_subcmd);
}

TEST(setValidFlags, testing)
{
    CLI cli;
    unordered_set<string> expected_sub;
    cli.setArguments({"MyProgram", "push", "-f", "all"});
    cli.setValidSubcommands({"push"});
    cli.setValidFlags("push", {"-f"});
    EXPECT_EQ(cli.isValidFlag("-f"), true);
    EXPECT_EQ(cli.isFlagSet("-f"), true);

    cli.setValidSubcommands({"pull", "pull jim hoe"});
    expected_sub = {"pull", "pull jim hoe", ""};
    EXPECT_EQ(cli.getValidSubcommands(), expected_sub);
    EXPECT_THROW(cli.setValidFlags("push", {"-f"}), CLIException);
    EXPECT_EQ(cli.getActiveSubcommand(), "");

    cli.setArguments({"MyProgram", "pull", "jim", "hoe", "-g", "value"});
    EXPECT_EQ(cli.getActiveSubcommand(), "pull jim hoe");
    cli.setValidFlags("pull jim hoe", {"-f"});
    EXPECT_EQ(cli.isValidFlag("-f"), true);
    EXPECT_EQ(cli.isFlagSet("-f"), false);
}

TEST(setValidFlags, multiple_single_flags)
{
    CLI cli;
    cli.setArguments({"MyProgram", "-hmv", "--help", "stuff"});
    cli.setValidSubcommands({});
    cli.setValidFlags({"-h", "--help", "-m", "-v"});
    EXPECT_EQ(cli.getFlagPosition("-h"), 1);
    EXPECT_EQ(cli.getFlagPosition("-m"), 1);
    EXPECT_EQ(cli.getFlagPosition("-v"), 1);
    EXPECT_EQ(cli.getFlagPosition("--help"), 2);
}

TEST(setValidFlags, substring_in_another_flag)
{
    CLI cli;
    cli.setArguments({"MyProgram", "-hmv", "--helpme", "stuff"});
    cli.setValidSubcommands({});
    cli.setValidFlags({"-h", "--help", "-m", "-v", "--helpme"});
    EXPECT_EQ(cli.getFlagPosition("-h"), 1);
    EXPECT_EQ(cli.getFlagPosition("-m"), 1);
    EXPECT_EQ(cli.getFlagPosition("-v"), 1);
    EXPECT_EQ(cli.getFlagPosition("--help"), -1);
    EXPECT_EQ(cli.getFlagPosition("--helpme"), 2);

    cli.setArguments({"MyProgram", "--help", "--helpme", "stuff"});
    EXPECT_EQ(cli.getFlagPosition("--help"), 1);
    EXPECT_EQ(cli.getFlagPosition("--helpme"), 2);

    cli.setArguments({"MyProgram", "--helpme", "--help", "stuff"});
    EXPECT_EQ(cli.getFlagPosition("--help"), 2);
    EXPECT_EQ(cli.getFlagPosition("--helpme"), 1);
}

TEST(setValidFlags, duplicate_flags_initialization)
{
    CLI cli;
    cli.setArguments({"MyProgram", "--help", "-h", "stuff"});
    cli.setValidFlags({"-h", "--help", "-h", "--help"});
    unordered_map<string, int> expected_flags = {{"-h", 2}, {"--help", 1}};
    EXPECT_EQ(cli.getFlags(), expected_flags);
}

TEST(setValidFlags, flags_with_invalid_prefix)
{
    CLI cli;
    cli.setArguments({"MyProgram", "--help", "-h", "stuff"});
    EXPECT_THROW(cli.setValidFlags({"--help", "/h"}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"---help"}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"money"}), CLIException);
}

TEST(setValidFlags, invalid_flags)
{
    CLI cli;
    cli.setArguments({"MyProgram", "--help", "-h", "stuff"});
    EXPECT_THROW(cli.setValidFlags({""}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"-"}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"--"}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"---"}), CLIException);
}

TEST(initialization, order)
{
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "-h", "val1", "--output", "val2"});
    cli.setValidSubcommands({"remote", "remote add"});
    cli.setValidFlags("remote add", {"-h", "--output", "-o"});
    unordered_set<string> expected_subs = {"remote", "remote add", ""};
    unordered_map<string, int> expected_flags = {{"-h", 3}, {"--output", 5}, {"-o", -1}};
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 2);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    EXPECT_EQ(cli.getFlags("remote add"), expected_flags);
}

TEST(checkers, testing)
{
    CLI cli;
    cli.setArguments({"MyProgram", "home", "-g"});
    EXPECT_EQ(cli.isValidFlag("-g"), false);
    EXPECT_THROW(cli.isFlagSet("-g"), CLIException);
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);

    cli.setValidFlags({"-g"});
    EXPECT_EQ(cli.isValidSubcommand("home"), false);
    EXPECT_EQ(cli.isValidFlag("-g"), true);
    EXPECT_EQ(cli.isFlagSet("-g"), true);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);

    cli.setValidSubcommands({"home", "init"}); // will reset valid flags
    EXPECT_EQ(cli.getActiveSubcommand(), "home");
    EXPECT_EQ(cli.isValidFlag("-g"), false);
    EXPECT_THROW(cli.isFlagSet("-g"), CLIException); // because "-g" is not a valid flag of "home"
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);

    EXPECT_THROW(cli.setValidFlags("test", {"--help"}), CLIException);
    cli.setValidFlags("home", {"-g", "--help"});
    cli.setArguments({"MyProgram", "home", "-g", "--help"});
    EXPECT_EQ(cli.getActiveSubcommand(), "home");
    EXPECT_EQ(cli.isValidFlag("-g"), true);
    EXPECT_EQ(cli.isValidFlag("--help"), true);
    EXPECT_EQ(cli.isFlagSet("-g"), true);
    EXPECT_EQ(cli.isFlagSet("--help"), true);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);
    EXPECT_EQ(cli.getFlagPosition("--help"), 3);

    cli.setArguments({"MyProgram", "init", "-g", "this"});
    EXPECT_EQ(cli.getActiveSubcommand(), "init");
    EXPECT_EQ(cli.isValidFlag("-g"), false);
    EXPECT_THROW(cli.isFlagSet("-g"), CLIException);
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);

    cli.setValidFlags("init", {"-g"});
    EXPECT_EQ(cli.isValidFlag("-g"), true);
    EXPECT_EQ(cli.isFlagSet("-g"), true);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);

    cli.setValidFlags("init", {"-h"});
    EXPECT_EQ(cli.isValidFlag("-g"), false); 
    EXPECT_THROW(cli.isFlagSet("-g"), CLIException); // "-g" flag no longer exists
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);
}

TEST(production, testing)
{
    // CLI cli({"MyProgram", "remote", "-h"});
    // unordered_map<string, unordered_map<string, int>> expected_subs;
    // cli.setValidSubcommands({"remote", "init", "remote add"}); 
    // cli.setValidFlags({"-h", "--help"}); 
    // cli.setValidFlags("init", {"-h", "-l"}); 
    // cli.setValidFlags("remote", {"-h"}); 
    // cli.setValidFlags("remote add", {"-h", "--help"}); 

    // cli.setArguments({"MyProgram", "remote", "add", "--help", "hello", "-a"});
    // expected_subs = {
    //     {"", {{"-h", -1}, {"--help", -1}}},
    //     {"init", {{"-h", -1}, {"-l", -1}}},
    //     {"remote", {{"-h", -1}}},
    //     {"remote add", {{"-h", -1}, {"--help", 3}}}
    // };
    // EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    // cli.setValidFlags("remote add", {"-h"});
    // EXPECT_THROW(cli.isFlagSet("remote add", "--help"), CLIException);
    // cli.setValidFlags("remote add", {"--help", "-a"});
    // EXPECT_EQ(cli.isFlagSet("remote add", "--help"), true);
    // EXPECT_EQ(cli.getFlagValue("--help"), "hello");
    // EXPECT_EQ(cli.getFlagValue("-a"), "");
}