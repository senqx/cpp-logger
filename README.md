# Logger - Lightweight C++ Logging Utility

## Overview
Logger is a thread-safe, lightweight logging utility for C++ applications, designed to support both terminal and file-based logging with customizable log levels.

## Features
- Thread-safe logging with mutex protection.
- Supports terminal and file output.
- ANSI color-coded logs for improved readability.
- Configurable log levels (Error, Warning, Info, Debug).
- Works on Windows and Linux/macOS.
- Lightweight and easy to integrate into existing projects.

## Installation
1. Clone the repository:
   git clone https://github.com/yourusername/logger.git
2. Include `logger.h` and `logger.cpp` in your project.
3. Compile normally with your project.

## Usage
### Basic Setup
```cpp
#include "logger.h"

int main() {
    Logger::enable_terminal_output();
    Logger::enable_file_output("app.log");

    Logger::error("This is a critical error!");
    Logger::warning("This is a warning.");
    Logger::info("This is an informational message.");
    Logger::debug("Debugging details here.");
    
    return 0;
}
```

### Logging Levels
The default logging level is Debug in development mode (`#ifndef NDEBUG`), but Info in release mode (`#define NDEBUG`).

Log Level | Description | Color
--------- | ----------- | ------
Error     | Critical errors | Red
Warning   | Potential issues | Yellow
Info      | Informational logs | White
Debug     | Debugging details | Cyan

### File Output
```cpp
Logger::enable_file_output("logs.txt");
```

Logs are automatically flushed and saved when the program exits.

## Running the Example
To build and run the example program:
1. Compile the project:
```
make
```
or for debugging:
```
make debug
```
2. Run the executable:
```
./bin/logger_test_release
```
or for debugging:
```
./bin/logger_test_debug
```
3. To clean build artifacts:
```
make clean
```

## Future Enhancements
- Asynchronous logging with a queue system.
- Configurable log format (JSON, CSV).
- Log file rotation support.

## License
MIT License. Free to use and modify.

