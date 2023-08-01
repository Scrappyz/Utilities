## Config::readConfigFromFile
Defined in header `config.hpp`

| |
| --- |
| void readConfigFromFile(const std::string& config_path, int error = 1) |

Reads the contents of a config file and initializes its contents accordingly.

## Parameters
`config_path` - the path to the config file \
`error` - throws an error if 1, not if 0

## Error
Throws an exception if `error` is 1.