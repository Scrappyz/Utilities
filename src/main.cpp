#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
using namespace utility::path;
namespace out = utility::print;
namespace fs = std::filesystem;

int main()
{
    // copy(joinPath(sourcePath(), "temp/any.txt"), joinPath(sourcePath(), "temp/temp1"));
    fs::copy_file(joinPath(sourcePath(), "temp/any.txt"), joinPath(sourcePath(), "temp/ex.txt"), fs::copy_options::skip_existing);
    return 0;
}