#ifndef __LOGGER__
#define __LOGGER__

#include <fstream>
#include <mutex>
#include <string_view>

/*!
 * @class Logger
 * @brief A simple thread-safe logging utility.
 */
class Logger {
  /*!
   * @enum MsgType
   * @brief Represents the type/severity of a log message.
   */
  enum class MsgType : int {
    Error = 0,
    Warning = 1,
    Info = 2,
    Debug = 3
  };

  //! Specifies the default logging level
  static constexpr MsgType s_level =
#ifdef NDEBUG
    MsgType::Info;
#else
    MsgType::Debug;
#endif

  static std::ofstream s_file;      //!< Log file output stream.
  static std::mutex s_mutex;        //!< Mutex for thread safety.
  static bool s_write_to_terminal;  //!< Flag to control terminal output.
  static bool s_ansi_supported;     //!< Flag to check color support.

  /*!
   * @brief Initializes the logger.
   * @note This function is called automatically during static initialization.
   */
  static void init();

  /*!
   * @brief Cleans up resources (closes log file).
   * @note This is automatically called at program exit.
   */
  static void cleanup();

  /*!
   * @brief Enables ANSI color codes for output (Windows compatibility fix).
   */
  static void enableAnsiCodes();

  /*!
   * @brief Prints a log message.
   * @param text The message to log.
   * @param type The severity/type of the message.
   * @param shouldFlush Whether to flush the log immediately.
   */
  static void print(std::string_view text, MsgType type, bool shouldFlush);

  static bool s_setup; //!< Tracks whether the logger has been initialized.

public:
  //! Deleted default constructor to prevent instantiation.
  Logger() = delete;

  /*!
   * @brief Enables logging to a specified file.
   * @param filename The name of the log file (default: "output.log").
   */
  static void enable_file_output(std::string_view filename = "output.log");

  /*!
   * @brief Enables terminal output for logs.
   */
  static void enable_terminal_output() {
    s_write_to_terminal = true;
  }

  /*!
   * @brief Disables terminal output for logs.
   */
  static void disable_terminal_output() { s_write_to_terminal = false; }

  /*!
   * @brief Logs an error message.
   * @param text The error message.
   */
  static void error(std::string_view text) {
    print(text, MsgType::Error, true);
  }

  /*!
   * @brief Logs a warning message.
   * @param text The warning message.
   */
  static void warning(std::string_view text) {
    if constexpr (MsgType::Warning <= s_level) {
      print(text, MsgType::Warning, false);
    }
  }

  /*!
   * @brief Logs an informational message.
   * @param text The informational message.
   */
  static void info(std::string_view text) {
    if constexpr (MsgType::Info <= s_level) {
      print(text, MsgType::Info, false);
    }
  }

  /*!
   * @brief Logs a debug message.
   * @param text The debug message.
   */
  static void debug(std::string_view text) {
    if constexpr (MsgType::Debug <= s_level) {
      print(text, MsgType::Debug, true);
    }
  }
};

#endif // __LOGGER__
