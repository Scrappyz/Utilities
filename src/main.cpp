#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "path.hpp"
#include "config.hpp"

void print(const std::filesystem::path& path)
{
    for(const auto& i : std::filesystem::recursive_directory_iterator(path)) {
        std::cout << i.path() << std::endl;
    }
}

void print(const std::unordered_set<std::filesystem::path>& paths)
{
    std::vector<std::filesystem::path> v;
    for(const auto& i : paths) {
        v.push_back(i);
    }

    std::sort(v.begin(), v.end());

    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
}

std::unordered_set<std::filesystem::path> getPathContent(const std::filesystem::path& path, bool include_parent = false)
{
    std::unordered_set<std::filesystem::path> result;
    std::filesystem::path relative_to = include_parent ? path.parent_path() : path;

    for(const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        result.insert(path::relative(entry.path(), relative_to));
    }

    return result;
}

bool testCopy(const std::filesystem::path& from, std::filesystem::path to)
{
    path::copy(from, to, path::CopyOption::SkipExisting);

    // "from" & "to": parent, parent
    // "from/" & "to": no parent, no parent
    // "from" & "to/": parent, parent
    // "from/" & "to/": no parent, no parent
    std::unordered_set<std::filesystem::path> c1 = getPathContent(from, !from.filename().empty());
    std::unordered_set<std::filesystem::path> c2 = getPathContent(to, false);

    bool result = true;
    for(const auto& i : c1) {
        if(c2.count(i) < 1) {
            result = false;
            continue;
        }
        std::string p = path::join(to, i);
        path::remove(p);
    }

    if(!from.filename().empty()) {
        path::remove(path::join(to, from.filename()));
    }

    return result;
}

bool testMove(const std::filesystem::path& from, const std::filesystem::path& to)
{
    bool from_has_end_separator = from.filename().empty();
    std::unordered_set<std::filesystem::path> c1 = getPathContent(from, !from_has_end_separator);

    path::move(from, to, path::CopyOption::SkipExisting);

    if(path::exists(from)) {
        return false;
    }

    std::unordered_set<std::filesystem::path> c2 = getPathContent(to, false);

    path::createDirectory(from);

    bool result = true;
    for(const auto& i : c1) {
        if(c2.count(i) < 1) {
            result = false;
            continue;
        }
        std::string p1 = path::join(to, i);
        std::string p2 = path::join(from.parent_path(), i);
        std::cout << "==================" << std::endl;
        std::cout << p1 << std::endl;
        std::cout << p2 << std::endl;
        path::move(p1, p2, path::CopyOption::SkipExisting);
    }

    if(!from_has_end_separator) {
        path::remove(path::join(to, from.filename()));
    }

    return result;
}

int main()
{
    std::string path = path::join(path::sourcePath(), "../../test/test_path/path");
    std::cout << testCopy(path::join(path, "sandbox/"), path::join(path, "temp"));
    return 0;
}