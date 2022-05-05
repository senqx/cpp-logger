#include "logger.hpp"

uint8_t Logger::_mode = 0;
bool Logger::_write_to_file = false;
size_t Logger::_file_write_count = 0;
std::fstream Logger::_file;

void Logger::print(uint8_t mode, std::string &text) {
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
            type = "INFO";
            color_mode = "\033[1;37m"; // Info
            break;
        default:
            type = "MESSAGE";
            color_mode = "\033[1;37m"; // Message (Default)
    }
    auto _time = std::chrono::system_clock::now();
    std::time_t n_time = std::chrono::system_clock::to_time_t(_time);
    std::string time = std::ctime(&n_time);
    time.pop_back();
    std::string output = color_mode + time+ " [" + type + "] \t" + text + " \033[0m\n";
    if(mode) {
        std::cout << output;
    } else {
        std::cerr << output;  
    }
    ++_file_write_count;
}

void Logger::set_mode(uint8_t mode=0) {
    if(mode > 2) {
        warning("Wrong mode number, so default is set instead");
    }
    _mode = mode;
}

void Logger::set_mode(std::string code) {
    for(int i = 0; i < code.size(); ++i) {
        code[i] = tolower(code[i]);
    }

    if(code == "error") {
        _mode = 0;
    } else if (code == "warning") {
        _mode = 1;
    } else if (code == "default") {
        _mode = 2;
    } else {
        warning("Wrong mode number, so default is set instead");
        _mode = 2;
    }
}

void Logger::set_output_filename(std::string filename) {
    _file.open(filename, std::ios::out);
    _write_to_file = true;
    if(!_file.is_open()) {
        warning("Couldn't open file: " + filename);
        _write_to_file = false;
    }
}

void Logger::error(std::string text) {
    print(0, text);
    if(_write_to_file) {
        _file << text;
        _file.flush();
        _file_write_count = 0;
    }
}

void Logger::warning(std::string text) {
    if(_mode >= 1) {
        print(1, text);
        if(_write_to_file) {
            _file << text;
            _file.flush();
            _file_write_count = 0;
        }
    }
}

void Logger::info(std::string text) {
    if(_mode == 2) {
        print(2, text);
        if(_write_to_file) {
            _file << text;
            if (_file_write_count == 100) {
                _file.flush();
                _file_write_count = 0;
            }
        }
    }
}

void Logger::debug(std::string text) {
    print(2, text);
    if(_write_to_file) {
        _file << text;
        if (_file_write_count == 100) {
            _file.flush();
            _file_write_count = 0;
        }
    }
}
