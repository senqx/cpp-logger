#ifndef __LOGGER__
#define __LOGGER__

#include <mutex>
#include <string_view>

class Logger {
  enum class MsgType : int {
    Error = 0,
    Warning = 1,
    Info = 2,
    Debug = 3
  };

  static constexpr MsgType s_level =
#ifdef NDEBUG
  MsgType::Info;
#else
  MsgType::Debug;
#endif

  static std::ofstream s_file;
  static bool s_write_to_terminal;
  static std::mutex s_mutex;

  static void print(std::string_view text, MsgType type);
  static void enable_file_output(std::string_view filename = "output.log");

public:
  Logger() = delete;

  static void enable_terminal_output() {
    s_write_to_terminal = true;
  }

  static void disable_terminal_output() {
    s_write_to_terminal = false;
  }

  static void error(std::string_view text) {
    print(text, MsgType::Error);
  }

  static void warning(std::string_view text) {
    if constexpr (MsgType::Warning <= s_level) {
      print(text, MsgType::Warning);
    }
  }

  static void info(std::string_view text) {
    if constexpr (MsgType::Info <= s_level) {
      print(text, MsgType::Info);
    }
  }

  static void debug(std::string_view text) {
    if constexpr (MsgType::Debug <= s_level) {
      print(text, MsgType::Debug);
    }
  }
};

#endif // __LOGGER__
