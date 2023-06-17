#include "cli.hpp"
#include <typeinfo>
#include <gtest/gtest.h>

using namespace std;

TEST(CLI, setArguments)
{
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "origin", "-h", "-o"});
    unordered_map<string, unordered_map<string,int>> expected_sub = {{"", unordered_map<string,int>()}};
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

TEST(CLI, setValidSubcommands)
{
    CLI cli({"MyProgram", "remote", "add", "--origin"});
    cli.setValidSubcommands({"pull", "push", "remote add"});
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 2);

    cli.setValidSubcommands({"", ""});
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 0);

    cli.setValidSubcommands({"", "  hello", "   hi   ", "boi   "});
    unordered_map<string, unordered_map<string, int>> expected_subcmd = {{"", unordered_map<string, int>()}, {"hello", unordered_map<string, int>()},
    {"hi", unordered_map<string, int>()}, {"boi", unordered_map<string, int>()}};
    EXPECT_EQ(cli.getMaxSubcommandChainCount(), 1);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subcmd);

    CLI cmd({"MyProgram"});
    unordered_map<string, unordered_map<string, int>> expected_sub = {{"", unordered_map<string, int>()}};
    cmd.setValidSubcommands({});
    EXPECT_EQ(cmd.getValidSubcommands(), expected_sub);
}

TEST(CLI, setValidFlags)
{
    CLI cli;
    unordered_map<string, unordered_map<string,int>> expected_sub;
    cli.setArguments({"MyProgram", "push", "-f", "all"});
    cli.setValidSubcommands({"push"});
    cli.setValidFlags("push", {"-f"});
    EXPECT_EQ(cli.isValidFlag("-f"), true);
    EXPECT_EQ(cli.isFlagSet("-f"), true);

    cli.setValidSubcommands({"pull", "pull jim hoe"});
    expected_sub = {{"pull", unordered_map<string,int>()}, {"", unordered_map<string,int>()}, {"pull jim hoe", unordered_map<string,int>()}};
    EXPECT_EQ(cli.getValidSubcommands(), expected_sub);
    EXPECT_THROW(cli.setValidFlags("push", {"-f"}), CLIException);
    EXPECT_EQ(cli.getActiveSubcommand(), "");

    cli.setArguments({"MyProgram", "pull", "jim", "hoe", "-g", "value"});
    EXPECT_EQ(cli.getActiveSubcommand(), "pull jim hoe");
    cli.setValidFlags("pull jim hoe", {"-f"});
    EXPECT_EQ(cli.isValidFlag("-f"), true);
    EXPECT_EQ(cli.isFlagSet("-f"), false);
}

TEST(CLI, checkers)
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

TEST(CLI, production)
{
    CLI cli({"MyProgram", "remote", "-h"});
    unordered_map<string, unordered_map<string, int>> expected_subs;
    cli.setValidSubcommands({"remote", "init", "remote add"}); 
    cli.setValidFlags({"-h", "--help"}); 
    cli.setValidFlags("init", {"-h", "-l"}); 
    cli.setValidFlags("remote", {"-h"}); 
    cli.setValidFlags("remote add", {"-h", "--help"}); 

    cli.setArguments({"MyProgram", "remote", "add", "--help", "hello", "-a"});
    expected_subs = {
        {"", {{"-h", -1}, {"--help", -1}}},
        {"init", {{"-h", -1}, {"-l", -1}}},
        {"remote", {{"-h", -1}}},
        {"remote add", {{"-h", -1}, {"--help", 3}}}
    };
    EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    cli.setValidFlags("remote add", {"-h"});
    EXPECT_THROW(cli.isFlagSet("remote add", "--help"), CLIException);
    cli.setValidFlags("remote add", {"--help", "-a"});
    EXPECT_EQ(cli.isFlagSet("remote add", "--help"), true);
    EXPECT_EQ(cli.getFlagValue("--help"), "hello");
    EXPECT_EQ(cli.getFlagValue("-a"), "");
}