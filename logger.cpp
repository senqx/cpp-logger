#include "logger.h"

#include <cctype>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

int Logger::_mode = 0;
bool Logger::_write_to_terminal = false;
size_t Logger::_file_write_count = 0;
std::fstream Logger::_file;

void Logger::print(const std::string& text, const int mode) {
  if(!_file.is_open()) {
    set_output_filename("output.log");
  }
	std::string color_mode;
	std::string type;
	switch(mode) {
		case 0:
			color_mode = "\033[1;31m"; // Error
			type = "ERROR";
			break;
		case 1:
			color_mode = "\033[1;33m"; // Warning
			type = "WARNING";
			break;
		case 2:
			type = "DEBUG";
			color_mode = "\033[1;37m"; // Debug
			break;
		default:
			type = "INFO";
			color_mode = "\033[1;37m"; // Info (Default)
	}

	const auto& _time = std::chrono::system_clock::now();
	const std::time_t n_time = std::chrono::system_clock::to_time_t(_time);
	std::string time = std::ctime(&n_time);
	time.pop_back();
	const std::string& output = time + " [" + type + "] \t" + text;

	++_file_write_count;
	_file << output << '\n';
    if(mode < 2) {
		_file.flush();
		_file_write_count = 0;
	} else {
		if (_file_write_count == 100) {
			_file.flush();
			_file_write_count = 0;
		}
	}

	if(_write_to_terminal) {
		if(mode) {
			std::cout << color_mode << output << "\033[0m\n";
		} else {
			std::cerr << color_mode << output << "\033[0m\n";
		}
	}
}

void Logger::set_mode(const std::string& mode) {
	if(mode == "error" || mode == "Error") {
		_mode = 0;
	} else if (mode == "warning" || mode == "Warning") {
		_mode = 1;
	} else if (mode == "default" || mode == "Default") {
		_mode = 2;
	} else {
		warning("Wrong mode name, so default is set instead");
		_mode = 2;
	}
}

void Logger::set_output_filename(const std::string& filename) {
	_file.open(filename, std::ios::out);
	if(!_file.is_open()) {
		// File wasn't opened so, using error() would be nonsense
		std::cerr << "Couldn't open file: " << filename << std::endl;
		exit(1);
	}
}

