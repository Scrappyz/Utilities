#include "utility.hpp"
#include <gtest/gtest.h>
#include <typeinfo>

using namespace std;
namespace mathUtil = utility::math;
namespace stringUtil = utility::string;
namespace parseUtil = utility::parse;

TEST(utility, isPrime)
{
    EXPECT_EQ(mathUtil::isPrime(1), false);
    EXPECT_EQ(mathUtil::isPrime(2), true);
    EXPECT_EQ(mathUtil::isPrime(27), false);
    EXPECT_EQ(mathUtil::isPrime(19), true);
    EXPECT_EQ(mathUtil::isPrime(97), true);
}

TEST(mod, general)
{
    EXPECT_EQ(mathUtil::mod(13, 5), 3);
    EXPECT_EQ(mathUtil::mod(8, 4), 0);
    EXPECT_EQ(mathUtil::mod(7, 2), 1);
    EXPECT_EQ(mathUtil::mod(-5, 3), 1);
    EXPECT_EQ(mathUtil::mod(3, 10), 3);
    EXPECT_EQ(mathUtil::mod(13, 10), 3);
    EXPECT_EQ(mathUtil::mod(-27, 10), 3);
    EXPECT_EQ(mathUtil::mod(-3, 11), 8);
    EXPECT_EQ(mathUtil::mod(-1, 11), 10);
}

TEST(gcd, general)
{
    EXPECT_EQ(mathUtil::gcd(2322, 654), 6);
    EXPECT_EQ(mathUtil::gcd(654, 2322), 6);
    EXPECT_EQ(mathUtil::gcd(270, 192), 6);
    EXPECT_EQ(mathUtil::gcd(192, 270), 6);
}

TEST(gcd, edge_case)
{
    EXPECT_EQ(mathUtil::gcd(0, 12), 12);
    EXPECT_EQ(mathUtil::gcd(12, 0), 12);
}

TEST(utility, getSum)
{
    EXPECT_EQ(mathUtil::getSum({2,4,6,8}), 20);
    EXPECT_EQ(mathUtil::getSum({1,2,3,4,5}), 15);
}

TEST(utility, getMean)
{
    EXPECT_EQ(mathUtil::getMean({2,4,6,8}), 5);
    EXPECT_EQ(mathUtil::getMean({1,2,3,4,5}), 3);
    EXPECT_EQ(mathUtil::getMean({2,8,6,12}), 7);
    EXPECT_EQ(mathUtil::getMean({5,5,5,2}), 4.25);
}

TEST(utility, getMedian)
{
    EXPECT_EQ(mathUtil::getMedian({1,2,3,4}), 2.5);
    EXPECT_EQ(mathUtil::getMedian({1,2,3,4,5}), 3);
}

TEST(utility, getMode)
{
    EXPECT_EQ(mathUtil::getMode({2,2,5,8,6}), vector<int>({2}));
    EXPECT_EQ(mathUtil::getMode({2,2,4,4,5,5,6,6}), vector<int>({6,5,4,2}));
    EXPECT_EQ(mathUtil::getMode<int>({}), vector<int>());

    EXPECT_EQ(mathUtil::getMode({"hello", "jim", "hello"}), vector<string>({"hello"}));
    EXPECT_EQ(mathUtil::getMode({"hello", "hi", "hi", "hello"}), vector<string>({"hi", "hello"}));
    EXPECT_EQ(mathUtil::getMode(vector<string>({"hello", "hi", "hi", "hello"})), vector<string>({"hi", "hello"}));
}

TEST(utility, getMidrange)
{
    EXPECT_EQ(mathUtil::getMidrange({1,2,3,4,5}), 3);
    EXPECT_EQ(mathUtil::getMidrange({5,8,9,2,3,10}), 6);
    EXPECT_EQ(mathUtil::getMidrange({5,89,7,4,1,3,0,5,8}), 44.5);
}

TEST(utility, precision)
{
    EXPECT_EQ(mathUtil::precision(1.69325, 2), 1.69);
    EXPECT_EQ(mathUtil::precision(6981.82967, 4), 6981.8296);
    EXPECT_EQ(mathUtil::precision(69, 5), 69);
    EXPECT_EQ(mathUtil::precision(85.85, 0), 85);
}

TEST(utility, toupper)
{
    string str = "abcd";
    EXPECT_EQ(stringUtil::toupper(str), "ABCD");

    str = "hello world!!/";
    EXPECT_EQ(stringUtil::toupper(str), "HELLO WORLD!!/");

    str = "HI MY NAME IS JIMBO!";
    EXPECT_EQ(stringUtil::toupper(str), "HI MY NAME IS JIMBO!");
}

TEST(utility, tolower)
{
    string str = "HELLO";
    EXPECT_EQ(stringUtil::tolower(str), "hello");

    str = "HELLO WORLD!!!/";
    EXPECT_EQ(stringUtil::tolower(str), "hello world!!!/");

    str = "hi my name is jimbo!";
    EXPECT_EQ(stringUtil::tolower(str), "hi my name is jimbo!");
}

TEST(utility, equalIgnoreCase)
{
    string str1 = "HELLO WORLD!!";
    string str2 = "hello world!!";
    EXPECT_EQ(stringUtil::equalIgnoreCase(str1, str2), true);
}

TEST(utility, trim)
{
    EXPECT_EQ(stringUtil::trim("a   b    c    d"), "a b c d");
    EXPECT_EQ(stringUtil::trim("    hello     world    "), "hello world");
    EXPECT_EQ(stringUtil::trim(""), "");
    EXPECT_EQ(stringUtil::trim("     "), "");
    EXPECT_EQ(stringUtil::trim("  higohgih   sohg is  iahgi"), "higohgih sohg is iahgi");
}

TEST(utility, split)
{
        // Test case 1: Empty string
    string input1 = "";
    string separators1 = ",";
    vector<string> expected1 = {};
    EXPECT_EQ(stringUtil::split(input1, separators1), expected1);

    // Test case 2: No separators
    string input2 = "hello world";
    string separators2 = ",";
    vector<string> expected2 = { "hello world" };
    EXPECT_EQ(stringUtil::split(input2, separators2), expected2);

    // Test case 3: Single separator
    string input3 = "hello,world";
    string separators3 = ",";
    vector<string> expected3 = { "hello", "world" };
    EXPECT_EQ(stringUtil::split(input3, separators3), expected3);

    // Test case 4: Multiple separators
    string input4 = "hello,world,,how,are,you";
    string separators4 = ",";
    vector<string> expected4 = { "hello", "world", "how", "are", "you" };
    EXPECT_EQ(stringUtil::split(input4, separators4), expected4);

    // Test case 5: Separator at beginning and end
    string input5 = ",hello,world,";
    string separators5 = ",";
    vector<string> expected5 = { "hello", "world" };
    EXPECT_EQ(stringUtil::split(input5, separators5), expected5);

    // Test case 6: Custom separators
    string input6 = "apple;banana;cherry";
    string separators6 = ";";
    vector<string> expected6 = { "apple", "banana", "cherry" };
    EXPECT_EQ(stringUtil::split(input6, separators6), expected6);

    // Test case 7: Empty separators
    string input7 = "hello world";
    string separators7 = "";
    vector<string> expected7 = { "hello world" };
    EXPECT_EQ(stringUtil::split(input7, separators7), expected7);
}

TEST(utility, startsWith)
{
    ASSERT_TRUE(stringUtil::startsWith("abcde", "abc"));
    ASSERT_TRUE(stringUtil::startsWith("abc", "abc"));
    ASSERT_FALSE(stringUtil::startsWith("ab", "abc"));
    ASSERT_FALSE(stringUtil::startsWith("accde", "abc"));
}

TEST(utility, endsWith)
{
    ASSERT_TRUE(stringUtil::endsWith("abcdef", "def"));
    ASSERT_TRUE(stringUtil::endsWith("abc", "abc"));
    ASSERT_FALSE(stringUtil::endsWith("ab", "abc"));
    ASSERT_FALSE(stringUtil::endsWith("abcd", "ab"));
}

TEST(utility, parseInteger)
{
    EXPECT_THROW(parseUtil::parseInteger(""), exception);
    EXPECT_EQ(parseUtil::parseInteger("159"), 159);
    EXPECT_THROW(parseUtil::parseInteger("s12"), exception);
    EXPECT_EQ(parseUtil::parseInteger("ss13", 1), 13);
    EXPECT_EQ(parseUtil::parseInteger("he11o w0rld", 1), 11);
    EXPECT_EQ(parseUtil::parseInteger("he11o w0rld", 2), 0);
    EXPECT_EQ(parseUtil::parseInteger("11 22 33", 3), 33);
    EXPECT_EQ(parseUtil::parseInteger("he11", 1), 11);
    EXPECT_THROW(parseUtil::parseInteger("hell"), exception);
    EXPECT_THROW(parseUtil::parseInteger("hell", 1), exception);
    EXPECT_THROW(parseUtil::parseInteger("he11", 2), exception);

    EXPECT_EQ(parseUtil::parseInteger('0'), 0);
    EXPECT_EQ(parseUtil::parseInteger('5'), 5);
    EXPECT_THROW(parseUtil::parseInteger('p'), exception);
}

TEST(utility, parseIntegers)
{
    vector<int> nums;
    EXPECT_THROW(parseUtil::parseIntegers(""), exception);
    EXPECT_EQ(parseUtil::parseIntegers("hello", 0), nums);
    EXPECT_EQ(parseUtil::parseIntegers("he11o", 0), nums);

    nums = {11};
    EXPECT_EQ(parseUtil::parseIntegers("he11o, wo12d", 1), nums);

    nums = {11, 12};
    EXPECT_EQ(parseUtil::parseIntegers("he11o wo12ld", 2), nums);
    EXPECT_EQ(parseUtil::parseIntegers("he11o w12ld"), nums);

    nums = {10, 11, 12, 13};
    EXPECT_EQ(parseUtil::parseIntegers(" 10 11 12  13  "), nums);
    EXPECT_EQ(parseUtil::parseIntegers(" 10 11 12  13  ", 6), nums);

    nums = {5};
    EXPECT_EQ(parseUtil::parseIntegers("5"), nums);
    EXPECT_EQ(parseUtil::parseIntegers("5", 5), nums);
}

TEST(utility, parseFloat)
{
    EXPECT_THROW(parseUtil::parseFloat(""), exception);
    EXPECT_EQ(parseUtil::parseFloat("11"), 11);
    EXPECT_EQ(parseUtil::parseFloat("11.59"), 11.59);
    EXPECT_THROW(parseUtil::parseFloat("ss11.59"), exception);

    EXPECT_EQ(parseUtil::parseFloat("ss11", 1), 11);
    EXPECT_EQ(parseUtil::parseFloat("ss11 s15k", 1), 11);
    EXPECT_EQ(parseUtil::parseFloat("ss11 s15ck", 2), 15);
    EXPECT_EQ(parseUtil::parseFloat("ss11 s15.69ck", 2), 15.69);
    EXPECT_EQ(parseUtil::parseFloat("  11  69.69  82.444  ", 2), 69.69);
}

TEST(utility, parseFloats)
{
    vector<double> nums;
    EXPECT_THROW(parseUtil::parseFloats(""), exception);
    EXPECT_EQ(parseUtil::parseFloats("hello", 0), nums);
    EXPECT_EQ(parseUtil::parseFloats("he11o", 0), nums);

    nums = {11};
    EXPECT_EQ(parseUtil::parseFloats("he11o, wo12d", 1), nums);

    nums = {11.5};
    EXPECT_EQ(parseUtil::parseFloats("he11.5o, wo12d", 1), nums);

    nums = {11, 12};
    EXPECT_EQ(parseUtil::parseFloats("he11o wo12ld", 2), nums);
    EXPECT_EQ(parseUtil::parseFloats("he11o w12ld"), nums);

    nums = {11.5, 12.63};
    EXPECT_EQ(parseUtil::parseFloats("he11.5o wo12.63ld", 2), nums);
    EXPECT_EQ(parseUtil::parseFloats("he11.5o w12.63ld"), nums);

    nums = {10, 11, 12.8, 13.3};
    EXPECT_EQ(parseUtil::parseFloats(" 10 11 12.8  13.3  "), nums);
    EXPECT_EQ(parseUtil::parseFloats(" 10 11 12.8  13.3  ", 6), nums);

    nums = {5.5};
    EXPECT_EQ(parseUtil::parseFloats("5.5"), nums);
    EXPECT_EQ(parseUtil::parseFloats("5.5", 5), nums);
}