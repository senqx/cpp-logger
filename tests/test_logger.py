import os
from pathlib import Path
import shlex
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
for mode in ("release", "debug"):
    run = subprocess.run([str(root / "bin" / f"logger_test_{mode}")], capture_output=True, text=True, check=True)
    assert "Sample error message" in run.stderr
    assert "Sample info message" in run.stdout
    assert ("Sample debug message" in run.stdout) == (mode == "debug")

source = r"""
#include "logger.h"
#include <string>
#include <thread>
#include <vector>
int main() {
  std::string name = "first.log.trailing";
  Logger::enable_file_output(std::string_view(name.data(), 9));
  Logger::info("first record");
  Logger::enable_file_output("missing-directory/fail.log");
  Logger::enable_file_output("second.log");
  std::vector<std::thread> threads;
  for (int t = 0; t < 4; ++t) threads.emplace_back([t] {
    for (int i = 0; i < 100; ++i) {
      Logger::disable_terminal_output();
      Logger::info("record " + std::to_string(t) + " " + std::to_string(i));
    }
  });
  for (auto& thread : threads) thread.join();
}
"""
with tempfile.TemporaryDirectory() as directory:
    work = Path(directory)
    (work / "test.cpp").write_text(source)
    compiler = shlex.split(os.environ.get("CXX", "g++"))
    subprocess.run(compiler + ["-std=c++17", "-Wall", "-Wextra", "-Werror", "-DNDEBUG", "-pthread", "-I" + str(root / "include"), str(work / "test.cpp"), str(root / "src/logger.cpp"), "-o", str(work / "test")], check=True)
    run = subprocess.run([str(work / "test")], cwd=work, capture_output=True, text=True, check=True)
    assert "Failed to open log file" in run.stderr
    assert "first record" in (work / "first.log").read_text()
    records = (work / "second.log").read_text().splitlines()
    assert len(records) == 400
    assert len(set(records)) == 400
    assert all(" [Info] record " in record and "\x1b" not in record for record in records)
print("PASS release/debug levels, file recovery, filename views, and 400 concurrent records")
