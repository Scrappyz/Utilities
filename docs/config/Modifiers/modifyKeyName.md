## Config::modifyKeyName
Defined in header `config.hpp`

| |
| --- |
| void modifyKeyName(const std::string& key, const std::string& new_key) |
| void modifyKeyName(const std::string& section, const std::string& key, const std::string& new_key) |

Renames the given key in the given section.

## Parameters
`section` - the section the key to rename is in \
`key` - the key to rename \
`new_key` - the new name for the key

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    config.addKey("new key");
    std::cout << config.doesKeyExist("new key") << std::endl;
    std::cout << config.doesKeyExist("renamed key") << std::endl;
    config.modifyKeyName("new key", "renamed key");
    std::cout << config.doesKeyExist("new key") << std::endl;
    std::cout << config.doesKeyExist("renamed key") << std::endl;

    return 0;
}
```

Output:
```
1
0
0
1
```