#ifndef __LOGGER__
#define __LOGGER__

#include <string>

/// Class Logger, simple class for better logging
class Logger {
  /// Mode, the mode that will be used for logging.
	// 0: only errors and info,
	// 1: print warnings, errors and info,
	// 2: print everything
  static int _mode;

  /// The File descriptor for logging (also) into a file
  static std::fstream _file;

  /// Flag, to enable logger output to terminal
  static bool _write_to_terminal;

  /// The count of logs into a file (Used for flushing)
  static size_t _file_write_count;

  /// The print body
  static void print(const std::string& text, const int mode=-1);

public:
  /// No objects shall be created
  Logger() = delete;

  /// Set mode
  static void set_mode(const int mode=0) {
    if(mode < 0 || mode > 2) {
      warning("Wrong mode number, so default is set instead");
    }
    _mode = mode;
  }

  /// Set mode (but if you like using words instead of numbers)
  static void set_mode(const std::string& code="Default");

  /// Specify the log output file name
  static void set_output_filename(const std::string& filename="output.log");

  /// Enable/Disable terminal output
	static void set_terminal_output(const bool arg) {
    _write_to_terminal = arg;
  }

	/// Print Error
  static void error(const std::string& text) {
    print(text, 0);
  }

  /// Print Warning
  static void warning(const std::string& text) {
    if(_mode >= 1) {
      print(text, 1);
    }
  }

  /// Print Log
  static void debug(const std::string& text) {
    if(_mode == 2) {
      print(text, 2);
    }
  }

  /// Print Info
  static void info(const std::string& text) {
    print(text);
  }

};

#endif

