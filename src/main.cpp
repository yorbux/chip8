#include "Arduino.h"
#include "config.hpp"
#include "rom.hpp"

void setup() {
    pinMode(BTN_NEXT_ROM_PIN, INPUT_PULLUP);
}

void loop() {
    if (!digitalRead(BTN_NEXT_ROM_PIN)) {
        next_rom();
    }
}