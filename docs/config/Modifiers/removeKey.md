## Config::removeKey
Defined in header `config.hpp`

| |
| --- |
| void removeKey(const std::string& key) |
| void removeKey(const std::string& section, const std::string& key) |

Removes a key from a section.

## Parameters
`section` - the section to remove the key from \
`key` - the key to remove

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    std::cout << config.doesKeyExist("new key") << std::endl;
    config.addKey("new key");
    std::cout << config.doesKeyExist("new key") << std::endl;
    config.removeKey("new key");
    std::cout << config.doesKeyExist("new key") << std::endl;

    return 0;
}
```

Output:
```
0
1
0
```