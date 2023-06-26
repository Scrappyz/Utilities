## path::sourcePath
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string sourcePath() |

## Return Value
Returns the absolute path to the executable.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::sourcePath() << endl;

    return 0;
}
```
Output:
```
D:\Documents\Codes\VS Code\C++\Utility\bin\Debug
```