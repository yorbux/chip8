#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "Arduino.h"
#include <memory>

#define BTN_NEXT_ROM_PIN GPIO_NUM_5

extern u_int8_t c_rom;
extern std::string roms[3];

extern uint16_t kbpins[];


#endif