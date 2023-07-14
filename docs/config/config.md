## Config Library
The config library is a config file parser in C++ that aims to simplify the process of the reading and writing of configuration files.

## Dependencies
### Minimum C++ Version
- [C++11](https://en.cppreference.com/w/cpp/11)

### Includes
- [\<string>](https://en.cppreference.com/w/cpp/string/basic_string)
- [\<vector>](https://en.cppreference.com/w/cpp/container/vector)
- [\<unordered_map>](https://en.cppreference.com/w/cpp/container/unordered_map)
- [\<fstream>](https://en.cppreference.com/w/cpp/io/basic_fstream)

## Format
The config library is capable of parsing files that can be read in plain text such as `txt` files. It can parse plain text that follows this format:
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
Each group of keys can be divided into sections and each key can be assigned a value with the `=` symbol.

## Usage
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
First we initialize the `Config` object by passing in the path to the configuration file. Then we can access its values with the method [getValueOf](Methods/getValueOf.md). You can pass a key to it or you can pass both the section and key you are trying to get the value of. \
Using the example in the [format](#format) section, the output would be:
```
val1
val2
val3
val 4
```

## Constructors
Defined in header `config.hpp`

| | |
| --- | --- |
| [(constructors)](Methods/constructors.md) | initializes the `Config` object with the contents of the given configuration file |

## Getters
Defined in header `config.hpp`

| | |
| --- | --- |
| [getValueOf](Methods/getValueOf.md) | returns the value of the key in the given section |

## Setters
Defined in header `config.hpp`

| | |
| --- | --- |
| [setConfig](Methods/setConfig.md) | initializes the `Config` object with the contents of the given configuration file |

## Modifiers
Defined in header `config.hpp`

| | |
| --- | --- |
| [modifyValueInFile](Methods/modifyValueInFile.md) | modifies the value of the given section and key in a config file <br> (static) |




