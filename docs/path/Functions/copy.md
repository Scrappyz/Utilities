## path::copy
Defined in header `path.hpp`

| Declarations |
| --- |
| void copy(const std::filesystem::path& from, const std::filesystem::path& to, const CopyOption& op = CopyOption::None) |

## Parameters
`from` - the source file/directory to copy \
`to` - the destination file/directory to copy to \
`op` - option what to do with existing files (see [CopyOption](../Enums/CopyOption.md))

## Notes
- If there is a directory separator at the end of the `from` path, it will only copy the contents of the source directory.

## Example
### Example 1
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    // create a directory "sandbox" in "temp" then copy its contents
    path::copy("sandbox", "temp"); 

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
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
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
    // only copy the contents of "sandbox" into "temp"
    path::copy("sandbox/", "temp"); // directory separator at the end of "sandbox"

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
+-- sandbox/
|   +-- sand.txt
|   +-- sandmore.txt
|   +-- subbox/
|       +-- stuff.txt
+-- temp/
    +-- sand.txt
    +-- sandmore.txt
    +-- subbox/
    |   +-- stuff.txt
    +-- temp.txt
    +-- test.txt
```
