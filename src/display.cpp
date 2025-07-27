#include "Arduino.h"
#include "U8g2lib.h"
#include "chip8.hpp"
#include "logger.hpp"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

void d_init() {
    oled.begin();
    oled.clearDisplay();
    oled.clearBuffer();
    oled.setFont(u8g2_font_ncenB08_tr);  // Fuente básica
    oled.drawStr(10, 30, "OLED OK!");    // Texto de prueba
    oled.sendBuffer(); 
    log("Display ready", LogLevel::INFO);
}

void d_draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height) {
    oled.clearBuffer(); // Siempre limpia antes de dibujar

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (framebuffer[y][x]) {
                oled.drawBox(x * 2, y * 2, 2, 2);
            }
        }
    }
}

void d_update() {
    oled.sendBuffer();
    oled.clearBuffer();
}