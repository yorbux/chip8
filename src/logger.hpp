#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <fstream>
#include <memory>

/// @brief define los niveles de severidad de los mensajes
enum LogLevel {
    NONE = 1,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    DEBUG = 4
};

/// @brief Imprime valores en el log con ciertos valores de severidad.
/// @param message contiene el mensaje que se desea mostrar
/// @param log_level define la severidad del mensaje
void log(std::string message, LogLevel log_level);

/// @brief permite establecer un nivel de seriedad
/// @param log_level define la seriedad del mensaje
void set_log_level(LogLevel log_level);

/// @brief funcion que transforma uint16_t a hex
/// @param val valor que se desea transforma a hex
/// @return returna un string en representancion hex
std::string to_hex(uint16_t val);

#endif