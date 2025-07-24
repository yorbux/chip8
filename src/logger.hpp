#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <fstream>
#include <memory>

enum LogLevel {
    NONE = 1,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    DEBUG = 4
};

void log(std::string message, LogLevel log_level);
void set_log_level(LogLevel log_level);

#endif