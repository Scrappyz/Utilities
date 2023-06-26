## path::SizeMetric
Defined in header `path.hpp`

| Members | Description |
| --- | --- |
| Byte | returns the size in bytes (default) |
| Kilobyte | returns the size in kilobytes |
| Megabyte | returns the size in megabytes |
| Gigabyte | returns the size in gigabytes |

## Example 
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::fileSize("Utility.exe") << " Bytes" << endl;
    cout << path::fileSize("Utility.exe", path::SizeMetric::Kilobyte) << " KB" << endl;
    cout << path::fileSize("Utility.exe", path::SizeMetric::Megabyte) << " MB" << endl;
    cout << path::fileSize("Utility.exe", path::SizeMetric::Gigabyte) << " GB" << endl;

    return 0;
}
```
Output:
```
3.39109e+06 Bytes
3311.61 KB
3.23399 MB
0.0031582 GB
```