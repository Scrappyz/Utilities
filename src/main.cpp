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



int main()
{
    std::string path = path::join(path::sourcePath(), "../../test/test_path/path");
    
    return 0;
}