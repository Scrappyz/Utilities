## path::join
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string join(const std::filesystem::path& p1, const std::filesystem::path& p2) |
| std::string join(const std::vector&lt;std::filesystem::path&gt;& paths) |

## Parameters
`p1` - a path \
`p2` - another path \
`paths` - a list of paths

## Return Value
Concatenates two or more paths together.

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
    cout << path::join("a/b/c/d", "e/f/g") << endl;
    cout << path::join("a/b/c/d", "e/f/g/") << endl; // separator at the end will be preserved
    cout << path::join("a/b/c/d", "../..") << endl;
    cout << path::join("a/b/c/d", "../../") << endl; // separator at the end will be preserved
    cout << path::join({"a/b/c/d", "../..", "e/f/g", "h/i/.."}) << endl;
    cout << path::join({"a/b/c/d", "../..", "e/f/g", "h/i/../"}) << endl; // preserve end separator

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

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
| [std::vector](https://en.cppreference.com/w/cpp/container/vector) | a sequence container that encapsulates dynamic size arrays |