#include "keyboard.hpp"
#include "Arduino.h"
#include "logger.hpp"  // Asegúrate de tener un logger en C

static const uint8_t EspKB_PinsToKey[4][4] = {
    {0x1, 0x2, 0x3, 0xC},
    {0x4, 0x5, 0x6, 0xD},
    {0x7, 0x8, 0x9, 0xE},
    {0xA, 0x0, 0xB, 0xF}
};

// define los pines para el keyboard, los primeros 4 para la salida y los otros 4 de entrada
const uint16_t kbpins[] = { 
    GPIO_NUM_25, GPIO_NUM_27, GPIO_NUM_14, GPIO_NUM_26, // COLUMNS
    GPIO_NUM_34, GPIO_NUM_35, GPIO_NUM_32, GPIO_NUM_33  // ROWS
};

uint16_t pins[ESPKB_PIN_COUNT];

//EspKeyboard keyboard;
uint8_t key_map[16];


void k_init() {
    /// mapea el teclado de acuerdo a los pines establecidos en config.hpp
    for (int i = 0; i < 8; i++) {
        pins[i] = kbpins[i];
    }

    /// coloca los primeros cuatro pins en OUTPUT
    for (int i = 0; i < 4; i++) {
        pinMode(pins[i], OUTPUT);
    }

    /// coloca los otros 4 en modo de entrad con proteccion 
    for (int i = 0; i < 4; i++) {
        pinMode(pins[4 + i], INPUT_PULLUP);
    }

    log("Keyboard ready", LogLevel::INFO);
}

void k_update(uint8_t* key_map, bool* running) {
    for (int y = 0; y < 4; y++) {
        digitalWrite(pins[y], LOW);
        for (int x = 0; x < 4; x++) {
            key_map[EspKB_PinsToKey[x][y]] = !digitalRead(pins[4 + x]);
        }
        digitalWrite(pins[y], HIGH);
    }
}