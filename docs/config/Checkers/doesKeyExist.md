## Config::doesKeyExist
Defined in header `config.hpp`

| |
| --- |
| bool doesKeyExist(const std::string& key) |
| bool doesKeyExist(const std::string& section, const std::string& key) |

## Parameters
`section` - the section the key is in \
`key` - the key to check

## Return Value
Returns `true` if the key exists, `false` otherwise.

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
    return 0;
}
```

Output:
```
0
1
```