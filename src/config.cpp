#include <memory>
#include "Arduino.h"
#include "U8g2lib.h"

#include "display.hpp"
#include "roms.h"
#include "chip8.hpp"
#include "cpu.hpp"
#include "sound.hpp"
#include "keyboard.hpp"

u_int8_t c_rom = 0;
std::string roms[] = {"b", "p", "m"};

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
Display display;

// define los pines para el keyboard, los primeros 4 para la salida y los otros 4 de entrada
uint16_t kbpins[] = { 
    GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18, GPIO_NUM_19, // COLUMNS   
    GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_34, GPIO_NUM_35 // ROWS
};
EspKeyboard keyboard;
uint8_t key_map[16];

Chip8 emulator;


// define el pin 15, el canal en 4 y la frecuencia en 500
EspSound sound;

void init_globals() {
    //display.oled = &oled;  // asigna puntero correctamente
}

