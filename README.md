# cpp-logger
## Simple logger for c++
**logger** has 3 modes **Default or 0, Warning or 1, Debug or 2**<br>
**logger** has 4 logging types: **Info, Debug, Warning** and **Error** where<br>
  * **Info** prints in white (in any mode)<br>
  * **Debug** prints also in white but only in **Debug** mode (mode = 2)<br>
  * **Warning** prints in yellow (mode >= 1 that is **Warning** and **Debug**)<br>
  * **Error** prints in red (in any mode)<br>

## All types print date and time
You can also set the **output file name** to log both into the terminal and the file<br>
The **logger** is very simple<br>
You can even include as 1 file (cat logger.hpp logger.cpp > cpplogger)<br>
Everyone are welcome to use, modify, and share this logger in any project that they want<br>

_This is my very first project in github, any suggestions are welcome_

# Commands
## Setting mode
### Can be used anywhere in code (for example you want your code to print in one mode, after some time, you can freely change it to another)
```C++
Logger::set_mode(_MODE_);
```
where _MODE_ is either _0_, _1_, _2_ or _error_, _warning_, _default_ (method is case insensetive)

## Setting log file (creates the file if it didn't exist, overwrites it otherwise)
```C++
Logger::set_output_filename(_FILENAME_);
```
where _FILENAME_ is the name of output file 

## If you want to see your log also on terminal
```C++
Logger::set_terminal_output(true); // enable
// ...
// Some code
// ...
Logger::set_terminal_output(false); // disable
```

## Logging functions
```C++
Logger::error(_TEXT_);
Logger::warning(_TEXT_);
Logger::info(_TEXT_);
Logger::debug(_TEXT_);
```
