## Config::doesKeyHaveValue
Defined in header `config.hpp`

| |
| --- |
| bool doesKeyHaveValue(const std::string& key) |
| bool doesKeyHaveValue(const std::string& section, const std::string& key) |

## Parameters
`section` - the section the key is in \
`key` - the key to check

## Return Value
Returns `true` if the key has a value, `false` otherwise.

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    std::cout << (config.doesKeyExist("new key") && config.doesKeyHaveValue("new key")) << std::endl;
    config.addKeyValue("new key", "new val");
    std::cout << (config.doesKeyExist("new key") && config.doesKeyHaveValue("new key")) << std::endl;

    return 0;
}
```

Output:
```
0
1
```