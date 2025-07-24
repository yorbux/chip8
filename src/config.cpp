#include <memory>
#include "Arduino.h"
#include "U8g2lib.h"

#include "roms.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
u_int8_t c_rom = 0;
std::string roms[] = {"b", "p", "m"};

// define los pines para el keyboard, los primeros 4 para la salida y los otros 4 de entrada
uint16_t kbpins[] = { 
    GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18, GPIO_NUM_19, // COLUMNS   
    GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_34, GPIO_NUM_35 // ROWS
};
