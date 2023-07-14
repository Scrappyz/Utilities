## Config::modifyValueInFile
Defined in header `config.hpp`

| | 
| --- |
| static bool modifyValueInFile(const std::string& config_path, const std::string& key, const std::string& new_val) |
| static bool modifyValueInFile(const std::string& config_path, const std::string& section, const std::string& key, const std::string& new_val) |

Modifies the value of the given section and key in a config file.

## Parameters
`config_path` - the config file that will be modified
`section` - the section to look for the key
`key` - the key to modify the value of
`new_val` - the new value

## Return Value
Returns `true` if the value has been modified successfully, `false` otherwise.

## Error
Throws an exception if the config file could not be opened.

## Notes
- If not section is provided, it will modify the key with no section

## Example
```
#include <iostream>
#include "config.hpp"

using namespace std;

int main()
{
    std::string config_path = "config.txt";
    std::cout << Config::modifyValueInFile(config_path, "key1", "cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "key 3", "cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "key g3", "cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "Section 1", "key4", "my cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "Section 1", "key 5", "my cookie") << std::endl;
    std::cout << Config::modifyValueInFile(config_path, "Section 2", "key 5", "cookie monster") << std::endl;

    return 0;
}
```

config.txt before:
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

config.txt after:
```
# Comment
key1=cookie
key2 = val2   # some commment
"key 3" = cookie
key4 = "val 4"
"key 5" = "val 5"

[Section 1]
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "my cookie"
"key 5" = "my cookie"

[Section 2]
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "cookie monster"
```

Output:
```
1
1
0
1
1
1
```
