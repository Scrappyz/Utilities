## path::execute
Defined in header `path.hpp`
Defined in namespace `path`

| |
| --- |
| bool execute(const std::string& command, bool wait = false) |
| bool execute(const std::vector\<std::string>& command, bool wait = false) |
| bool execute(const std::initializer_list\<std::string>& command, bool wait = false) |

Executes the given command.

## Parameters
`command` - the command to execute \
`wait` - waits for the process to finish

## Return Value
Returns `true` if the command is executed successfully, `false` otherwise.

## Notes
- Using the list overload `{"my", "command and", "arguments"}` will be executed as `"my" "command and" "arguments"`.

