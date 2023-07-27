## Config::getValueOf
Defined in header `config.hpp`

| |
| --- |
| const std::string& getValueOf(const std::string& key) |
| const std::string& getValueOf(const std::string& section, const std::string& key) |

Get the value of the corresponding key in the given section.

## Parameters
`section` - the section to look for the key
`key` - the key to get the value of

## Return Value
Returns the value of the key in the given section.

## Error
Throws an out of range exception if the section or key does not exist.

## Notes
- Providing no section will return the value of the key that does not belong to any section.

## Example
File:
```
# Comment
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "val 5"

[Section 1]
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "val 5"

[Section 2]
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "val 5"
```

```
#include <iostream>
#include "config.hpp"

using namespace std;

int main()
{
    std::string config_path = "config.txt";
    Config config(config_path);
    std::cout << config.getValueOf("key1") << std::endl;
    std::cout << config.getValueOf("Section 1", "key2") << std::endl;
    std::cout << config.getValueOf("Section 2", "key 3") << std::endl;
    std::cout << config.getValueOf("Section 2", "key4") << std::endl;

    return 0;
}
```

Output:
```
val1
val2
val3
val 4
```