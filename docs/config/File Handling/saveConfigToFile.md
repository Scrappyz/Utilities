## Config::saveConfigToFile
Defined in header `config.hpp`

| |
| --- |
| void saveConfigToFile(const std::string& config_path) |

Saves the contents of the `Config` object to a file.

## Parameters
`config_path` - the path to the file where the config will be saved

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    Config config;

    config.addKeyValue("main", "main value");

    config.addSection("section 1");
    config.addKeyValue("section 1", "key 1", "hello");
    config.addKeyValue("section 1", "key2", "world");

    config.addSection("section 2");
    config.addKeyValue("section 2", "key1", "some value");
    config.addKeyValue("section 2", "key2", "some value");
    
    config.saveConfigToFile("test.txt");
    
    return 0;
}
```

test.txt:
```
main = "main value"

[section 1]
"key 1" = hello
key2 = world

[section 2]
key1 = "some value"
key2 = "some value"
```