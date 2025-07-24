#ifndef __ROM_HPP__
#define __ROM_HPP__

#include <cstdint>
#include <iostream>
#include "logger.hpp"

void load_rom(std::string& file_path, u_int8_t* mem);
void next_rom(void);

#endif