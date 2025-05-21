#include "logger.h"

int main() {
  Logger::enable_terminal_output();
  Logger::error("Sample error message");
  Logger::warning("Sample warning message");
  Logger::info("Sample info message");
  Logger::debug("Sample debug message");
  return 0;
}
