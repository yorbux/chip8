#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define ESPKB_PIN_COUNT 8
#define ESPKB_PIN_HALF  (ESPKB_PIN_COUNT / 2)

typedef struct {
    uint16_t pins[ESPKB_PIN_COUNT];
} EspKeyboard;

void k_init();
void k_update(uint8_t* key_map, bool* running);

#endif
