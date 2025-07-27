#ifndef __ROM_HPP__
#define __ROM_HPP__

#include <cstdint>
#include <iostream>
#include "logger.hpp"

extern std::string roms[];

/// @brief funcion que carga la rom en la memoria
/// @param file_path es la primera letra del nombre del ROM se usa para identificar la ROM a cargar
/// @param mem es la direccion de memoria en donde se desea escribir la rom
void load_rom(std::string& file_path, uint8_t* mem);

/// @brief funcion que permite cambiar las ROMS que estan definidas en roms.h
/// @param
void next_rom(void);

#endif