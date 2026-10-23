# cpp-logger

A small synchronous C++17 logger with terminal and file output. It provides Error, Warning, Info and Debug levels without third-party dependencies.

## Quick start

```sh
git clone https://github.com/senqx/cpp-logger.git
cd cpp-logger
make
./bin/logger_test_release
```

Build tools: a C++17 compiler, GNU Make and thread support. Linux is verified; Windows console-color support is implemented but not tested here.

To integrate it, add `include/` to your include path and compile `src/logger.cpp` with your application. Use consistent `NDEBUG` settings across all translation units. On Linux, compile and link with `-pthread`.

```cpp
#include "logger.h"

int main() {
    Logger::enable_terminal_output();
    Logger::enable_file_output("app.log");
    Logger::info("Application started");
    Logger::warning("Disk space is low");
    Logger::error("Could not open input");
    Logger::debug("Development details");
}
```

## Behavior

- Terminal output is disabled until enabled. Error messages use `stderr`; other levels use `stdout`.
- Release builds with `NDEBUG` omit Debug messages. Development builds include all four levels and print startup diagnostics.
- Records use local timestamps: `YYYY-MM-DD HH:MM:SS [Info] message`.
- POSIX terminal output includes ANSI colors, including when redirected. Windows enables colors when its console supports them.
- File output contains no color codes. Opening a file truncates it; opening another flushes and closes the previous file. Parent directories must already exist.
- Log writes, file changes and terminal toggles use one mutex. There is no background queue, rotation or runtime level selection.
- Errors and Debug messages flush immediately. Release builds also flush periodically; normal process exit flushes and closes the file. Abnormal termination can lose buffered output.

This is a small utility, not a durable audit log. File-open failures are reported to `stderr`; write failures are not exposed through the API. Avoid logging from static constructors/destructors or signal handlers.

## Development

```sh
make debug
./bin/logger_test_debug
make test
```

`make test` requires Python 3 and checks release/debug levels, file reopening, non-null-terminated filename views, and concurrent logging. Build variants use separate object directories so switching modes does not reuse incompatible objects.

## License

[MIT](LICENSE).
