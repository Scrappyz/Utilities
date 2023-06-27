## path::fileSize
Defined in header `path.hpp`

| Declarations |
| --- |
| double fileSize(const std::filesystem::path& path, const SizeMetric& metric = SizeMetric::Byte) |

## Parameters
`path` - the path to get the size of \
`metric` - the unit of measurement of the file size (see [SizeMetric](../Enums/SizeMetric.md))

## Return Value
Returns a `double` that represents the size of the given path in the given size metric.

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

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
| [SizeMetric](../Enums/SizeMetric.md) | specifies what unit of measurement to use in file sizes |