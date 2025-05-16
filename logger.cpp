#include "logger.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>

std::ofstream Logger::s_file;
bool Logger::s_write_to_terminal = false;
std::mutex Logger::s_mutex;

static constexpr std::string_view COLOR_CODES[] = {
  "\033[1;31m", // Error (Red)
  "\033[1;33m", // Warning (Yellow)
  "\033[1;37m", // Info (White)
  "\033[1;36m"  // Debug (Cyan)
};

static constexpr std::string_view LOG_TYPE_PREFIXES[] = {
  "[Error] ",
  "[Warning] ",
  "[Info] ",
  "[Debug] "
};

void Logger::enable_file_output(std::string_view filename) {
  std::lock_guard<std::mutex> lock(s_mutex);

  if (std::filesystem::exists(filename.data())) {
    int version = 1;
    std::string new_filename;
    do {
      new_filename = std::string(filename) + "_v" + std::to_string(version);
      ++version;
    } while (std::filesystem::exists(new_filename));

    filename = new_filename;
  }

  s_file.open(filename.data(), std::ios::out | std::ios::trunc);
  if (!s_file.is_open()) {
    std::cerr << "Failed to open log file: " << filename << std::endl;
  }
}

void Logger::print(std::string_view text, MsgType type) {
  std::lock_guard<std::mutex> lock(s_mutex);

#ifdef NDEBUG
  static int log_count = 0;
#endif

  std::ostringstream output;
  const auto now = std::chrono::system_clock::now();
  const std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::string timestamp = std::ctime(&time);
  timestamp[timestamp.size() - 1] = ' '; // Change newline into a space.

  output << timestamp << LOG_TYPE_PREFIXES[static_cast<int>(type)] << text;

  // Terminal output with color
  if (s_write_to_terminal) {
    (type == MsgType::Error ? std::cerr : std::cout)
      << COLOR_CODES[static_cast<int>(type)] << output.str() << "\033[0m\n";
  }

  // File output with batch flushing
  if (s_file.is_open()) {
    s_file << output.str() << '\n';

#ifdef NDEBUG
    ++log_count
    if (log_count >= 500) {
        s_file.flush();
        log_count = 0;
    }
#else
    s_file.flush();
#endif
  }
}
