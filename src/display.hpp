#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <cstdint>
#include "U8g2lib.h"

/// @brief inicializa la pantalla mediante u8g2, configura la comunicacion I2C y tambien limpia la pantalla
void d_init();
/// @brief funcion usada para dibujar en la pantalla
/// @param framebuffer contiene el buffer de la pantalla
/// @param width el ancho de pantalla en este caso 64
/// @param height el alto de la pantalla en este caso 32
void d_draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height);

/// actualiza la pantalla limpiando el buffer y enviado el buffer
void d_update();

#endif