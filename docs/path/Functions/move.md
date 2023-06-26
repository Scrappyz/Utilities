## path::move
Defined in header `path.hpp`

| Declarations |
| --- |
| void move(const std::filesystem::path& from, const std::filesystem::path& to, const CopyOption& op = CopyOption::None) |

## Parameters
`from` - the source file/directory to move \
`to` - the destination file/directory to move to \
`op` - option to do with existing files (see [CopyOption](../Enums/CopyOption.md))

## Notes
- If there is a directory separator at the end of the `from` path, it will only move the contents of the source directory.
- If the move operation fails or is cancelled midway, the source file will be preserved.

## Example
### Example 1
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    // create a directory "sandbox" in "temp" then move its contents
    path::move("sandbox", "temp");

    return 0;
}
```
Before running code:
```
Debug/
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- temp.txt
    +-- test.txt
```
After running code:
```
Debug/
+-- temp/
    +-- sandbox/
    |   +-- sand.txt
    |   +-- sandmore.txt
    |   +-- subbox/
    |       +-- stuff.txt
    +-- temp.txt
    +-- test.txt
```

### Example 2
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    // only move the contents of "sandbox" into "temp"
    path::move("sandbox/", "temp"); // directory separator at the end of "sandbox"

    return 0;
}
```
Before running code:
```
Debug/
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- temp.txt
    +-- test.txt
```
After running code:
```
Debug/
+-- temp/
    +-- sand.txt
    +-- sandmore.txt
    +-- subbox/
    |   +-- stuff.txt
    +-- temp.txt
    +-- test.txt
```