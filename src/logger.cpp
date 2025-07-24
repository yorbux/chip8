#include <iostream>
#include <memory>
#include <string>
#include "logger.hpp"

using namespace std;

static LogLevel c_log_level = LogLevel::DEBUG;

void log(string message, LogLevel log_level) {
    string buffer = "";

    if (log_level <= c_log_level) {
        switch (log_level)
        {
        case LogLevel::ERROR:
            buffer += "\033[31m[ERROR]";
            break;
        case LogLevel::WARN: 
            buffer += "\033[33m[WARN] "; 
            break;
        case LogLevel::INFO: 
            buffer += "\033[32m[INFO] "; 
            break;
        case LogLevel::DEBUG: 
            buffer += "\033[0m[DEBUG] "; 
            break;
        default:
            break;
        }
    }

    buffer += message + "\n";

    cout << buffer;
}

void set_log_level(LogLevel log_level) {
    c_log_level = log_level;
}