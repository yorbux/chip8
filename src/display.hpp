#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <cstdint>
#include "U8g2lib.h"


struct Display {
    U8G2* oled;
};

void d_init();
void d_draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height);
void d_update();

#endif