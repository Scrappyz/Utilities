#include "cli.hpp"
#include <typeinfo>
#include <gtest/gtest.h>

using namespace std;

TEST(setArguments, general)
{
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "origin", "-h", "-o"});
    unordered_set<string> expected_sub = {""};
    EXPECT_EQ(cli.getValidSubcommands(), expected_sub);
    EXPECT_EQ(cli.getActiveSubcommand(), "");
    //EXPECT_EQ(cli.getMaxSubcommandChainCount(), 0);
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
    EXPECT_EQ(cli.isFlagActive("-h"), true);
    cli.setArguments({"MyProgram", "remote", "add", "--help"});
    EXPECT_EQ(cli.isFlagActive("remote", "-h"), false);
    EXPECT_EQ(cli.isFlagActive("--help"), true);
}

TEST(setValidSubcommands, general)
{
    CLI cli({"MyProgram", "remote", "add", "--origin"});
    cli.setValidSubcommands({"pull", "push", "remote add"});
    //EXPECT_EQ(cli.getMaxSubcommandChainCount(), 2);

    cli.setValidSubcommands({"", ""});
    //EXPECT_EQ(cli.getMaxSubcommandChainCount(), 0);

    cli.setValidSubcommands({"", "  hello", "   hi   ", "boi   "});
    unordered_set<string> expected_subcmd = {"", "hello", "hi", "boi"};
    //EXPECT_EQ(cli.getMaxSubcommandChainCount(), 1);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subcmd);

    CLI cmd({"MyProgram"});
    expected_subcmd = {""};
    cmd.setValidSubcommands({});
    EXPECT_EQ(cmd.getValidSubcommands(), expected_subcmd);
}

TEST(setValidFlags, general)
{
    CLI cli;
    unordered_set<string> expected_sub;
    cli.setArguments({"MyProgram", "push", "-f", "all"});
    cli.setValidSubcommands({"push"});
    cli.setValidFlags("push", {"-f"});
    EXPECT_EQ(cli.isValidFlag("-f"), true);
    EXPECT_EQ(cli.isFlagActive("-f"), true);

    cli.setValidSubcommands({"pull", "pull jim hoe"});
    expected_sub = {"pull", "pull jim hoe", ""};
    EXPECT_EQ(cli.getValidSubcommands(), expected_sub);
    EXPECT_THROW(cli.setValidFlags("push", {"-f"}), CLIException);
    EXPECT_EQ(cli.getActiveSubcommand(), "");

    cli.setArguments({"MyProgram", "pull", "jim", "hoe", "-g", "value"});
    EXPECT_EQ(cli.getActiveSubcommand(), "pull jim hoe");
    cli.setValidFlags("pull jim hoe", {"-f"});
    EXPECT_EQ(cli.isValidFlag("-f"), true);
    EXPECT_EQ(cli.isFlagActive("-f"), false);
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

    cli.setArguments({"MyProgram", "-hmv", "-gc", "--hello"});
    cli.setValidFlags({"-h", "-m", "-v", "-g", "-c", "--hello"});
    EXPECT_EQ(cli.getFlagPosition("-h"), 1);
    EXPECT_EQ(cli.getFlagPosition("-m"), 1);
    EXPECT_EQ(cli.getFlagPosition("-v"), 1);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);
    EXPECT_EQ(cli.getFlagPosition("-c"), 2);
    EXPECT_EQ(cli.getFlagPosition("--hello"), 3);
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

TEST(setValidFlags, duplicate_flags)
{
    CLI cli;
    cli.setArguments({"MyProgram", "--help", "--help"});
    cli.setValidFlags({"--help"});
    EXPECT_EQ(cli.getFlagPosition("--help"), 2);

    cli.setArguments({"MyProgram", "--flag=value", "--flag"});
    cli.setValidFlags({"--flag"});
    EXPECT_EQ(cli.getFlagPosition("--flag"), 2);
    EXPECT_EQ(cli.getValuesOf("--flag"), vector<string>());
}

TEST(setValidFlags, flags_with_invalid_prefix)
{
    CLI cli;
    cli.setArguments({"MyProgram", "--help", "-h", "stuff"});
    EXPECT_THROW(cli.setValidFlags({"--help", "/h"}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"---help"}), CLIException);
    EXPECT_THROW(cli.setValidFlags({"money"}), CLIException);
}

TEST(setValidFlags, edge_cases)
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
    // initialization order test
    vector<string> expected_args = {"MyProgram", "remote", "add", "-h", "val1", "--output", "val2"};
    unordered_set<string> expected_subs = {"remote", "remote add", ""};
    unordered_map<string, int> expected_flags = {{"-h", 3}, {"--output", 5}, {"-o", -1}};

    // args -> subcommands -> flags
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "-h", "val1", "--output", "val2"});
    cli.setValidSubcommands({"remote", "remote add"});
    cli.setValidFlags("remote add", {"-h", "--output", "-o"});
    EXPECT_EQ(cli.getArguments(), expected_args);
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 2);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    EXPECT_EQ(cli.getFlags("remote add"), expected_flags);

    // subcommands -> args -> flags
    cli.clear();
    cli.setValidSubcommands({"remote", "remote add"});
    cli.setArguments({"MyProgram", "remote", "add", "-h", "val1", "--output", "val2"});
    cli.setValidFlags("remote add", {"-h", "--output", "-o"});
    EXPECT_EQ(cli.getArguments(), expected_args);
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 2);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    EXPECT_EQ(cli.getFlags("remote add"), expected_flags);

    // flags -> subcommands -> args
    cli.clear();
    expected_flags.clear();
    EXPECT_THROW(cli.setValidFlags("remote add", {"-h", "--output", "-o"}), CLIException); // subcommands have not been set yet
    cli.setValidSubcommands({"remote", "remote add"});
    cli.setArguments({"MyProgram", "remote", "add", "-h", "val1", "--output", "val2"});
    EXPECT_EQ(cli.getArguments(), expected_args);
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 2);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    EXPECT_EQ(cli.getFlags("remote add"), expected_flags);

    // flags -> args -> subcommands
    cli.clear();
    EXPECT_THROW(cli.setValidFlags("remote add", {"-h", "--output", "-o"}), CLIException);
    cli.setArguments({"MyProgram", "remote", "add", "-h", "val1", "--output", "val2"});
    cli.setValidSubcommands({"remote", "remote add"});
    EXPECT_EQ(cli.getArguments(), expected_args);
    EXPECT_EQ(cli.getActiveSubcommand(), "remote add");
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), 2);
    EXPECT_EQ(cli.getValidSubcommands(), expected_subs);
    EXPECT_EQ(cli.getFlags("remote add"), expected_flags);
}

TEST(getArgumentAt, concatenation)
{
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "--help", "value", "lol"});
    EXPECT_EQ(cli.getArgumentAt(0), "MyProgram");
    EXPECT_EQ(cli.getArgumentAt(2, 6), "add");
    EXPECT_THROW(cli.getArgumentAt(-1, 2), CLIException);
    EXPECT_THROW(cli.getArgumentAt(6, 2), CLIException);
    EXPECT_EQ(cli.getArgumentAt(0, 2), "MyProgram remote add");
    EXPECT_EQ(cli.getArgumentAt(3, 5), "--help value lol");
    EXPECT_EQ(cli.getArgumentAt(3, 2), "");
}

TEST(getValuesOf, general)
{
    CLI cli;
    cli.setArguments({"MyProgram", "--flag=value"});
    cli.setValidFlags({"--flag"});
    vector<string> flag_val = {"value"};
    EXPECT_EQ(cli.getValuesOf("--flag"), flag_val);
}

TEST(getValuesOf, multiple_values)
{
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "val1", "val2", "--flag", "fval1", "fval2", "-h", "hval1", "hval2", "hval3",
    "-m=mval1", "mval2", "mval3"});
    cli.setValidSubcommands({"remote add"});
    cli.setValidFlags("remote add", {"--flag", "-h", "-m"});
    vector<string> expected_values = {"val1", "val2"};
    EXPECT_EQ(cli.getValuesOf("remote add"), expected_values);
    expected_values = {"fval1", "fval2"};
    EXPECT_EQ(cli.getValuesOf("--flag"), expected_values);
    expected_values = {"hval1", "hval2"};
    EXPECT_EQ(cli.getValuesOf("-h", 2), expected_values);
    expected_values = {"mval1", "mval2", "mval3"};
    EXPECT_EQ(cli.getValuesOf("-m"), expected_values);
    expected_values = {"mval1"};
    EXPECT_EQ(cli.getValuesOf("-m", 1), expected_values);
}

TEST(getValuesOf, no_value)
{
    CLI cli;
    cli.setArguments({"MyProgram", "add"});
    cli.setValidSubcommands({"add"});
    vector<string> expected_values;
    EXPECT_EQ(cli.getValuesOf("add"), expected_values);

    cli.setArguments({"MyProgram", "add", "val1"});
    expected_values = {};
    EXPECT_EQ(cli.getValuesOf("add", 0), expected_values);

    cli.setArguments({"MyProgram", "add", "-f", "val1"});
    cli.setValidFlags({"-f"});
    expected_values = {};
    EXPECT_EQ(cli.getValuesOf("-f", 0), expected_values);
}

TEST(getFlagValues, general)
{
    unordered_map<string, vector<string>> expected_values;
    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "val1", "val2", "--flag=fval1", "fval2", "-h", "hval1", "hval2"});
    cli.setValidSubcommands({"remote add", "remote"});
    cli.setValidFlags("remote add", {"--flag", "-h", "--help"});

    expected_values = {{"", {"val1", "val2"}}, {"--flag", {"fval1", "fval2"}}, {"-h", {"hval1", "hval2"}}};
    EXPECT_EQ(cli.getFlagValues(), expected_values);

    cli.setArguments({"MyProgram", "val1", "val2", "--flag=fval1", "fval2", "-h", "hval1", "hval2"});
    cli.setValidFlags({"--flag", "-h", "--help"});
    EXPECT_EQ(cli.getFlagValues(), expected_values);

    cli.setArguments({"MyProgram", "--flag=fval1", "fval2", "-h", "hval1", "hval2"});
    expected_values = {{"", {}}, {"--flag", {"fval1", "fval2"}}, {"-h", {"hval1", "hval2"}}};
    EXPECT_EQ(cli.getFlagValues(), expected_values);
}

TEST(checkers, general)
{
    CLI cli;
    cli.setArguments({"MyProgram", "home", "-g"});
    EXPECT_EQ(cli.isValidFlag("-g"), false);
    EXPECT_THROW(cli.isFlagActive("-g"), CLIException);
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);

    cli.setValidFlags({"-g"});
    EXPECT_EQ(cli.isValidSubcommand("home"), false);
    EXPECT_EQ(cli.isValidFlag("-g"), true);
    EXPECT_EQ(cli.isFlagActive("-g"), true);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);

    cli.setValidSubcommands({"home", "init"}); // will reset valid flags
    EXPECT_EQ(cli.getActiveSubcommand(), "home");
    EXPECT_EQ(cli.isValidFlag("-g"), false);
    EXPECT_THROW(cli.isFlagActive("-g"), CLIException); // because "-g" is not a valid flag of "home"
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);

    EXPECT_THROW(cli.setValidFlags("test", {"--help"}), CLIException);
    cli.setValidFlags("home", {"-g", "--help"});
    cli.setArguments({"MyProgram", "home", "-g", "--help"});
    EXPECT_EQ(cli.getActiveSubcommand(), "home");
    EXPECT_EQ(cli.isValidFlag("-g"), true);
    EXPECT_EQ(cli.isValidFlag("--help"), true);
    EXPECT_EQ(cli.isFlagActive("-g"), true);
    EXPECT_EQ(cli.isFlagActive("--help"), true);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);
    EXPECT_EQ(cli.getFlagPosition("--help"), 3);

    cli.setArguments({"MyProgram", "init", "-g", "this"});
    EXPECT_EQ(cli.getActiveSubcommand(), "init");
    EXPECT_EQ(cli.isValidFlag("-g"), false);
    EXPECT_THROW(cli.isFlagActive("-g"), CLIException);
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);

    cli.setValidFlags("init", {"-g"});
    EXPECT_EQ(cli.isValidFlag("-g"), true);
    EXPECT_EQ(cli.isFlagActive("-g"), true);
    EXPECT_EQ(cli.getFlagPosition("-g"), 2);

    cli.setValidFlags("init", {"-h"});
    EXPECT_EQ(cli.isValidFlag("-g"), false); 
    EXPECT_THROW(cli.isFlagActive("-g"), CLIException); // "-g" flag no longer exists
    EXPECT_THROW(cli.getFlagPosition("-g"), CLIException);
}

TEST(clear, general)
{
    vector<string> expected_args;
    unordered_map<string, unordered_map<string, int>> expected_subs = {{"", unordered_map<string, int>()}};
    string expected_active_sub;
    int expected_sub_end_pos = 0;
    int expected_max_chain = 0;

    CLI cli;
    cli.setArguments({"MyProgram", "remote", "add", "-h", "hello"});
    cli.setValidSubcommands({"remote", "remote add", "status"});
    cli.setValidFlags({"-h", "--help", "--force"});
    cli.clear();
    EXPECT_EQ(cli.getArguments(), expected_args);
    EXPECT_EQ(cli.getSubcommands(), expected_subs);
    EXPECT_EQ(cli.getActiveSubcommand(), expected_active_sub);
    EXPECT_EQ(cli.getActiveSubcommandEndPosition(), expected_sub_end_pos);
}