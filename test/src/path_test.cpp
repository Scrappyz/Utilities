#include <unordered_set>
#include "path.hpp"
#include "gtest/gtest.h"

using namespace path;

std::string test_path = path::joinPath(path::sourcePath(), "../test_path/path");

std::unordered_set<std::filesystem::path> getPathContent(const std::filesystem::path& path, bool include_parent = false)
{
    std::unordered_set<std::filesystem::path> result;
    std::filesystem::path relative_to = include_parent ? path.parent_path() : path;

    for(const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        result.insert(path::relativePath(entry.path(), relative_to));
    }

    return result;
}

bool testCopy(const std::filesystem::path& from, std::filesystem::path to) // good
{
    path::copy(from, to, path::CopyOption::SkipExisting);

    std::unordered_set<std::filesystem::path> c1 = getPathContent(from, !from.filename().empty());
    std::unordered_set<std::filesystem::path> c2 = getPathContent(to, false);

    bool result = true;
    for(const auto& i : c1) {
        if(c2.count(i) < 1) {
            result = false;
            continue;
        }
        path::remove(path::joinPath(to, i));
    }

    if(!from.filename().empty()) {
        path::remove(path::joinPath(to, from.filename()));
    }

    return result;
}

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

TEST(joins, edge_case)
{
    EXPECT_EQ(joinPath({}), "");
    EXPECT_EQ(joinPath({"", "", "", ""}), "");
    EXPECT_EQ(joinPath({"", "a/b", "", "c/d"}), "a\\b\\c\\d");
    EXPECT_EQ(joinPath({"", "a/b", "", "c/d/"}), "a\\b\\c\\d\\");
}

TEST(joins, concatenate)
{
    EXPECT_EQ(joinPath({"a/b/c"}), "a\\b\\c");
    EXPECT_EQ(joinPath({"a/b/c/"}), "a\\b\\c\\");
    EXPECT_EQ(joinPath({"a/b/c", "d/e"}), "a\\b\\c\\d\\e");
    EXPECT_EQ(joinPath({"a/b/c", "d/e/"}), "a\\b\\c\\d\\e\\");
    EXPECT_EQ(joinPath({"a/b/c/d", "e", "f", "g/h"}), "a\\b\\c\\d\\e\\f\\g\\h");
    EXPECT_EQ(joinPath({"a/b/c/d", "e", "f", "g/h/"}), "a\\b\\c\\d\\e\\f\\g\\h\\");
    EXPECT_EQ(joinPath({"a/b/c/d", "e/", "f/", "g/h/"}), "a\\b\\c\\d\\e\\f\\g\\h\\");
}

TEST(joins, end_separator)
{
    EXPECT_EQ(joinPath({"a/b/c/d/../.."}), "a\\b");
    EXPECT_EQ(joinPath({"a/b/c/d/../../"}), "a\\b\\");
    EXPECT_EQ(joinPath({"a/b/c/d/../../", "e/f/..", "g"}), "a\\b\\e\\g");
    EXPECT_EQ(joinPath({"a/b/c/d/../../", "e/f/..", "g/"}), "a\\b\\e\\g\\");
}

TEST(hasSameContent, not_exist)
{
    EXPECT_THROW(hasSameContent("__wassup__.txt", "__hello.txt"), std::exception);
    EXPECT_THROW(hasSameContent(path::joinPath(test_path, "temp/shaggy.txt"), "__wassup__.txt"), std::exception);
    EXPECT_THROW(hasSameContent("__wassup.txt", path::joinPath(test_path, "temp/shaggy.txt")), std::exception);
}

TEST(hasSameContent, not_same_type)
{
    EXPECT_THROW(hasSameContent(path::joinPath(test_path, "temp"), path::joinPath(test_path, "temp/shaggy.txt")), std::exception);
    EXPECT_THROW(hasSameContent(path::joinPath(test_path, "temp/shaggy.txt"), path::joinPath(test_path, "temp")), std::exception);
}

TEST(hasSameContent, directories)
{
    ASSERT_TRUE(hasSameContent(path::joinPath(test_path, "same1"), path::joinPath(test_path, "same2")));
    ASSERT_FALSE(hasSameContent(path::joinPath(test_path, "same1"), path::joinPath(test_path, "temp")));
}

TEST(hasSameContent, files)
{
    ASSERT_TRUE(hasSameContent(path::joinPath(test_path, "temp/shaggy.txt"), path::joinPath(test_path, "temp/shaggy1.txt")));
    ASSERT_FALSE(hasSameContent(path::joinPath(test_path, "temp/sand1.txt"), path::joinPath(test_path, "temp/shaggy.txt")));
}

TEST(copy, general)
{
    ASSERT_TRUE(testCopy(path::joinPath(test_path, "same1"), path::joinPath(test_path, "temp")));
    ASSERT_TRUE(testCopy(path::joinPath(test_path, "same1/"), path::joinPath(test_path, "temp")));
}