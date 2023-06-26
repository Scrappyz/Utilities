## path::directorySeparator
Defined in header `path.hpp`

| Declarations |
| --- |
| char directorySeparator() |

## Return Value
Returns a directory separator character of your designated operating system.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

// On Windows
int main()
{
    cout << path::directorySeparator() << endl;

    return 0;
}
```
Output:
```
\
```