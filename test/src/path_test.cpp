#include "path.hpp"
#include "gtest/gtest.h"

using namespace path;

TEST(isValidFilenameChar, check)
{
    EXPECT_EQ(isValidFilenameChar('<'), false);
    EXPECT_EQ(isValidFilenameChar('>'), false);
    EXPECT_EQ(isValidFilenameChar('|'), false);
    EXPECT_EQ(isValidFilenameChar(':'), false);
    EXPECT_EQ(isValidFilenameChar('\"'), false);
    EXPECT_EQ(isValidFilenameChar('\\'), false);
    EXPECT_EQ(isValidFilenameChar('/'), false);
    EXPECT_EQ(isValidFilenameChar('?'), false);
    EXPECT_EQ(isValidFilenameChar('*'), false);
    EXPECT_EQ(isValidFilenameChar('t'), true);
}

TEST(hasFileExtension, check)
{
    EXPECT_EQ(hasFileExtension("test.txt"), true);
    EXPECT_EQ(hasFileExtension(".git"), false);
    EXPECT_EQ(hasFileExtension(".txt"), false);
    EXPECT_EQ(hasFileExtension("a.txt"), true);
    EXPECT_EQ(hasFileExtension("/at.txt"), true);
    EXPECT_EQ(hasFileExtension("/.txt"), false);
    EXPECT_EQ(hasFileExtension("/test.txt/"), true);
    EXPECT_EQ(hasFileExtension("test..txt"), true);
    EXPECT_EQ(hasFileExtension("test.txt//"), true);
    EXPECT_EQ(hasFileExtension("test.num.txt"), true);
    EXPECT_EQ(hasFileExtension("test..num..txt"), true);
    EXPECT_EQ(hasFileExtension("sandbox/file.txt"), true);
    EXPECT_EQ(hasFileExtension("foo/bar/koo"), false);
    EXPECT_EQ(hasFileExtension("foo/bar/koo.cpp"), true);
    EXPECT_EQ(hasFileExtension("foo/bar/koo.cpp//"), true);
    EXPECT_EQ(hasFileExtension("foo/bar/file."), false);
}

TEST(fileExtension, getExtension)
{
    EXPECT_EQ(fileExtension("test.txt"), "txt");
    EXPECT_EQ(fileExtension(".git"), "");
    EXPECT_EQ(fileExtension(".txt"), "");
    EXPECT_EQ(fileExtension("a.txt"), "txt");
    EXPECT_EQ(fileExtension("/at.txt"), "txt");
    EXPECT_EQ(fileExtension("/.txt"), "");
    EXPECT_EQ(fileExtension("/test.txt/"), "txt");
    EXPECT_EQ(fileExtension("test..txt"), "txt");
    EXPECT_EQ(fileExtension("test.txt//"), "txt");
    EXPECT_EQ(fileExtension("test.num.txt"), "txt");
    EXPECT_EQ(fileExtension("test..num..txt"), "txt");
    EXPECT_EQ(fileExtension("sandbox/file.txt"), "txt");
    EXPECT_EQ(fileExtension("foo/bar/koo"), "");
    EXPECT_EQ(fileExtension("foo/bar/koo.cpp"), "cpp");
    EXPECT_EQ(fileExtension("foo/bar/koo.cpp//"), "cpp");
    EXPECT_EQ(fileExtension("foo/bar/file."), "");
}

TEST(joinPath, edge_case)
{
    EXPECT_EQ(joinPath("", ""), "");
    EXPECT_EQ(joinPath("a/b/c", ""), "a\\b\\c");
    EXPECT_EQ(joinPath("a/b/c/", ""), "a\\b\\c\\");
    EXPECT_EQ(joinPath("", "a/b/c"), "a\\b\\c");
    EXPECT_EQ(joinPath("", "a/b/c/"), "a\\b\\c\\");
}

TEST(joinPath, concatenate)
{
    EXPECT_EQ(joinPath("a/b/c", "d/e"), "a\\b\\c\\d\\e");
    EXPECT_EQ(joinPath("a/b/c", "d/e/"), "a\\b\\c\\d\\e\\");
    EXPECT_EQ(joinPath("a/b/c/", "d/e"), "a\\b\\c\\d\\e");
}

TEST(joinPath, end_separator)
{
    EXPECT_EQ(joinPath("a/b/c/d", ".."), "a\\b\\c");
    EXPECT_EQ(joinPath("a/b/c/d", "../"), "a\\b\\c\\");
    EXPECT_EQ(joinPath("a/b/c/d", "../.."), "a\\b");
    EXPECT_EQ(joinPath("a/b/c/d", "../../"), "a\\b\\");
    EXPECT_EQ(joinPath("a/b/c/d", "."), "a\\b\\c\\d");
    EXPECT_EQ(joinPath("a/b/c/d", "./"), "a\\b\\c\\d\\");
    EXPECT_EQ(joinPath("a/b/c/d/..", ""), "a\\b\\c");
    EXPECT_EQ(joinPath("a/b/c/d/../", ""), "a\\b\\c\\");
    EXPECT_EQ(joinPath("a/b/c/d/../../e", ""), "a\\b\\e");
    EXPECT_EQ(joinPath("a/b/c/d/../../e/", ""), "a\\b\\e\\");
    EXPECT_EQ(joinPath("", "a/b/c/d/../../e"), "a\\b\\e");
    EXPECT_EQ(joinPath("", "a/b/c/d/../../e/"), "a\\b\\e\\");
}

TEST(joinPaths, edge_case)
{
    EXPECT_EQ(joinPath({}), "");
    EXPECT_EQ(joinPath({"", "", "", ""}), "");
    EXPECT_EQ(joinPath({"", "a/b", "", "c/d"}), "a\\b\\c\\d");
    EXPECT_EQ(joinPath({"", "a/b", "", "c/d/"}), "a\\b\\c\\d\\");
}

TEST(joinPaths, concatenate)
{
    EXPECT_EQ(joinPath({"a/b/c"}), "a\\b\\c");
    EXPECT_EQ(joinPath({"a/b/c/"}), "a\\b\\c\\");
    EXPECT_EQ(joinPath({"a/b/c", "d/e"}), "a\\b\\c\\d\\e");
    EXPECT_EQ(joinPath({"a/b/c", "d/e/"}), "a\\b\\c\\d\\e\\");
    EXPECT_EQ(joinPath({"a/b/c/d", "e", "f", "g/h"}), "a\\b\\c\\d\\e\\f\\g\\h");
    EXPECT_EQ(joinPath({"a/b/c/d", "e", "f", "g/h/"}), "a\\b\\c\\d\\e\\f\\g\\h\\");
    EXPECT_EQ(joinPath({"a/b/c/d", "e/", "f/", "g/h/"}), "a\\b\\c\\d\\e\\f\\g\\h\\");
}

TEST(joinPaths, end_separator)
{
    EXPECT_EQ(joinPath({"a/b/c/d/../.."}), "a\\b");
    EXPECT_EQ(joinPath({"a/b/c/d/../../"}), "a\\b\\");
    EXPECT_EQ(joinPath({"a/b/c/d/../../", "e/f/..", "g"}), "a\\b\\e\\g");
    EXPECT_EQ(joinPath({"a/b/c/d/../../", "e/f/..", "g/"}), "a\\b\\e\\g\\");
}