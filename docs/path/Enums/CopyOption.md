## path::CopyOption
Defined in header `path.hpp`

| Members | Description
| --- | --- |
| None | prompts the user what to do if a file already exists (default) |
| SkipExisting | skips all existing files |
| OverwriteExisting | overwrites all existing files |

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    path::copy("temp/test.txt", "temp/another.txt");

    return 0;
}
```
Output:
```
[Warning] "another.txt" already exists. Would you like to overwrite?
[Y] for yes, [N] for no, [A] for yes to all, [X] to cancel:
```