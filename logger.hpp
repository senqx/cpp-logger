#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cctype>

/// Class Logger, simple class for better logging
class Logger {
    /// Mode, the mode that will be used for logging. 0: only errors and debug messages, 1: print warnings, errors and debug messages, 2: print everything
    static uint8_t _mode;

    /// The print body
    static void print(uint8_t mode, std::string &text);

    /// The File descriptor for logging (also) into a file
    static std::fstream _file;

    /// Flag, to check if you want also to log into a file
    static bool _write_to_file;

    /// The count of logs into a file (Used for flushing)
    static size_t _file_write_count;

public:
    /// No objects shall be created
    Logger() = delete;

    /// Set mode
    static void set_mode(uint8_t mode);

    /// Set mode (but if you like to use words instead of numbers)
    static void set_mode(std::string code);

    /// Specify the log output file name (also sets the "_write_to_flag" flag)
    static void set_output_filename(std::string filename);

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
