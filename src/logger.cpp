#include "logger.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>

#ifdef _WIN32
#include <windows.h>
#endif

std::ofstream Logger::s_file;
std::mutex Logger::s_mutex;
bool Logger::s_write_to_terminal = false;
bool Logger::s_ansi_supported = false;

bool Logger::s_setup = ([] {
  Logger::init();
  std::atexit(Logger::cleanup);
  return true;
})();

static constexpr unsigned char flush_threshold = 255;

static constexpr std::string_view COLOR_CODES[] = {
  "\033[1;31m", // Error (Red)
  "\033[1;33m", // Warning (Yellow)
  "\033[1;37m", // Info (White)
  "\033[1;36m"  // Debug (Cyan)
};

static constexpr std::string_view LOG_TYPE_PREFIXES[] = {
  " [Error] ",
  " [Warning] ",
  " [Info] ",
  " [Debug] "
};

void Logger::enableAnsiCodes() {
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD mode;
  if (GetConsoleMode(hConsole, &mode)) {
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (SetConsoleMode(hConsole, mode)) {
      s_ansi_supported = true;
    }
  }
#else
  s_ansi_supported = true; // Assume ANSI support on POSIX systems.
#endif
}

void Logger::init() {
  enableAnsiCodes();
#ifndef NDEBUG
  std::cout << "ANSI supported: " << s_ansi_supported << '\n';
  std::cout << "Logger is set up and is working on mode: "
            << ((s_level == MsgType::Debug) ? "debug" : "normal") << std::endl;
#endif
}
// Cleanup: Ensures all logs are saved before exit.
void Logger::cleanup() {
  std::lock_guard<std::mutex> lock(s_mutex);
  if (s_file.is_open()) {
    s_file.flush();
    s_file.close();
  }
}

void Logger::enable_file_output(std::string_view filename) {
  std::lock_guard<std::mutex> lock(s_mutex);
  s_file.open(filename.data(), std::ios::out | std::ios::trunc);
  if (!s_file.is_open()) {
    std::cerr << "Failed to open log file: " << filename << std::endl;
  }
}

void Logger::print(std::string_view text, MsgType type, bool shouldFlush) {
  std::lock_guard<std::mutex> lock(s_mutex);

#ifdef NDEBUG
  static unsigned int counter = 0;
  ++counter;
  if (counter >= flush_threshold) {
    shouldFlush = true;
    counter = 0;
  }
#endif

  const auto now = std::chrono::system_clock::now();
  std::time_t time_now = std::chrono::system_clock::to_time_t(now);
  std::tm timeinfo;
#ifdef _WIN32
  localtime_s(&timeinfo, &time_now);
#else
  localtime_r(&time_now, &timeinfo);
#endif
  char timestamp[20]; // "YYYY-MM-DD HH:MM:SS" = 19 chars + '\0'.
  std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

  const int index = static_cast<int>(type);
  std::ostringstream oss;
  oss << timestamp << LOG_TYPE_PREFIXES[index] << text;

  if (s_write_to_terminal) {
    std::ostream& out = (type == MsgType::Error) ? std::cerr : std::cout;
    if (s_ansi_supported) {
      out << COLOR_CODES[index];
    }
    out << oss.str() << "\033[0m\n";
    if (shouldFlush) {
      out.flush();
    }
  }

  if (s_file.is_open()) {
    s_file << oss.str() << '\n';
    if (shouldFlush) {
      s_file.flush();
    }
  }
}
