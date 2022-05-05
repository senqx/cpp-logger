# cpp-logger
## Simple logger for c++
**logger** has 3 modes **Default, Warning, Debug**<br>
**logger** has 4 logging types: **Info, Debug, Warning** and **Error** where<br>
**Info** prints in **bold** white (in any mode)<br>
**Debug** prints also in **bold** white but only in debug mode (mode = 2)<br>
**Warning** prints in **bold** yellow (mode >= 1)<br>
**Error** prints in **bold** red (in any mode)<br>

## All types print date and time
You can also set the **output file name** to log both into the terminal and the file<br>
The **logger** is very simple<br>
You can even include as 1 file (cat logger.hpp logger.cpp > cpplogger)<br>
Everyone is welcome to use, modify, and share this logger in any project that they want<br>

_This is my very first project in github, any suggestions are welcome_

# Commands
## Setting mode
### Can be used anywhere in code (for example you want your code to print in one mode, after some time, you can freely change it to another)
Logger::set_mode(MODE); where MODE is either 0, 1, 2 or error, warning, default (method is case insensetive)

## Setting log file (creates the file if it didn't exist, overwrites it otherwise)
Logger::set_output_filename(FILENAME); where FILENAME is the name of output file 

## Logging functions
Logger::error(TEXT);
Logger::warning(TEXT);
Logger::info(TEXT);
Logger::debug(TEXT);

