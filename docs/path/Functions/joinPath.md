## path::joinPath
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string joinPath(const std::filesystem::path& p1, const std::filesystem::path& p2) |
| std::string joinPath(const std::vector&lt;std::filesystem::path&gt;& paths) |

## Parameters
`p1` - a path
`p2` - another path
`paths` - a list of paths

## Return Value
Concatenates two paths or a list of paths.

## Notes
- If there is a directory separator at the end of the last path, it will preserve the separator.
- Will replace all directory separators to your operating system's preferred separator.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::joinPath("a/b/c/d", "e/f/g") << endl;
    cout << path::joinPath("a/b/c/d", "e/f/g/") << endl; // separator at the end will be preserved
    cout << path::joinPath("a/b/c/d", "../..") << endl;
    cout << path::joinPath("a/b/c/d", "../../") << endl; // separator at the end will be preserved
    cout << path::joinPath({"a/b/c/d", "../..", "e/f/g", "h/i/.."}) << endl;
    cout << path::joinPath({"a/b/c/d", "../..", "e/f/g", "h/i/../"}) << endl; // preserve end separator

    return 0;
}
```
Output:
```
a\b\c\d\e\f\g
a\b\c\d\e\f\g\
a\b
a\b\
a\b\e\f\g\h
a\b\e\f\g\h\
```