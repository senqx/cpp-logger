#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cctype>

/// Class Logger, simple class for better logging
class Logger {
    /// Mode, the mode that will be used for logging.
	// 0: only errors and info,
	// 1: print warnings, errors and info,
	// 2: print everything
    static uint8_t _mode;

    /// The print body
    static void print(uint8_t mode, std::string &text);

    /// The File descriptor for logging (also) into a file
    static std::fstream _file;

    /// Flag, to enable logger output to terminal
    static bool _write_to_terminal;

    /// The count of logs into a file (Used for flushing)
    static size_t _file_write_count;

public:
    /// No objects shall be created
    Logger() = delete;

    /// Set mode
    static void set_mode(uint8_t mode);

    /// Set mode (but if you like using words instead of numbers)
    static void set_mode(std::string code);

    /// Specify the log output file name
    static void set_output_filename(std::string filename = "output.log");

    /// Enable/Disable terminal output
	static void set_terminal_output(bool arg);

	/// Print Error
    static void error(std::string text);

    /// Print Warning
    static void warning(std::string text);

    /// Print Info
    static void info(std::string text);

    /// Print Log
    static void debug(std::string text);

};

#endif
