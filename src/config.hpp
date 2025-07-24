#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "Arduino.h"
#include "U8g2lib.h"
#include <memory>

#include "chip8.hpp"
#include "cpu.hpp"

#define BTN_NEXT_ROM_PIN GPIO_NUM_5

extern u_int8_t c_rom;
extern Chip8 emulator;
extern std::string roms[3];

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;
extern Display display;

extern uint16_t kbpins[];

void init_globals();

#endif