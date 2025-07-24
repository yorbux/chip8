#include "keyboard.hpp"
#include "Arduino.h"
#include "config.hpp"
#include "logger.hpp"  // Asegúrate de tener un logger en C

static const uint8_t EspKB_PinsToKey[4][4] = {
    {0x1, 0x2, 0x3, 0xC},
    {0x4, 0x5, 0x6, 0xD},
    {0x7, 0x8, 0x9, 0xE},
    {0xA, 0x0, 0xB, 0xF}
};

EspKeyboard kb;

void k_init() {
    for (int i = 0; i < 8; i++) {
        kb.pins[i] = kbpins[i];
    }

    for (int i = 0; i < 4; i++) {
        pinMode(kb.pins[i], OUTPUT);
    }

    for (int i = 0; i < 4; i++) {
        pinMode(kb.pins[4 + i], INPUT_PULLUP);
    }

    log("Keyboard ready", LogLevel::INFO);
}

void k_update(uint8_t* key_map, bool* running) {
    for (int y = 0; y < 4; y++) {
        digitalWrite(kb.pins[y], LOW);
        for (int x = 0; x < 4; x++) {
            key_map[EspKB_PinsToKey[x][y]] = !digitalRead(kb.pins[4 + x]);
        }
        digitalWrite(kb.pins[y], HIGH);
    }
}