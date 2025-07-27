#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Arduino.h"
#include <stdint.h>
#include <stdbool.h>

#define ESPKB_PIN_COUNT 8
#define ESPKB_PIN_HALF  (ESPKB_PIN_COUNT / 2)

/// @brief inicializa el keyboard y mapea los pins en la estructura
void k_init();
/// @brief verifica si alguna fila del teclado matricial esta activa o un baton fue presionado
/// @param key_map es el mapeo del teclado
/// @param running
void k_update(uint8_t* key_map, bool* running);

#endif
