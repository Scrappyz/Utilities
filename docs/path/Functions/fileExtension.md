## path::fileExtension
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string fileExtension(const std::filesystem::path& path) |

## Parameters
`path` - the path or filename to extract the file extension from

## Return Value
Returns the file extension of a given path or filename, returns an empty string if there is no file extension found.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << "\"" << path::fileExtension("test.txt") << "\"" << endl;
    cout << "\"" << path::fileExtension(".git") << "\"" << endl;
    cout << "\"" << path::fileExtension("a.txt") << "\"" << endl;
    cout << "\"" << path::fileExtension("test..txt") << "\"" << endl;
    cout << "\"" << path::fileExtension("test.num.txt") << "\"" << endl;
    cout << "\"" << path::fileExtension("foo/bar/koo") << "\"" << endl;
    cout << "\"" << path::fileExtension("foo/bar/koo.cpp") << "\"" << endl;

    return 0;
}
```
Output:
```
"txt"
""
"txt"
"txt"
"txt"
""
"cpp"
```