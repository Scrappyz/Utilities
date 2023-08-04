## Path::hasSameContent
Defined in `path.hpp`

| |
| --- |
| bool hasSameContent(const std::filesystem::path& p1, const std::filesystem::path& p2) |

Checks if two directories have the same files or if two files have the same data. 

## Parameters
`p1` - a file or directory \
`p2` - a file or directory

## Return Value
Returns `true` if a two directories have the same files or if two files have the same data, `false` otherwise.

## Error
Throws an exception if:
- `p1` or `p2` does not exist.
- `p1` and `p2` are not of the same type eg: `p1` is a file and `p2` is a directory.

## Example
dir1:
```
dir1/
+-- d.txt
+-- doo/
|   +-- arg.txt
+-- srcs.jpg
```

dir2:
```
dir2/
+-- d.txt
+-- doo/
|   +-- arg.txt
+-- srcs.jpg
```

```
#include <iostream>
#include "path.hpp"

int main()
{
    std::string p1 = "dir1";
    std::string p2 = "dir2;

    std::cout << path::hasSameContent(p1, p2);

    return 0;
}
```

Output:
```
1
```