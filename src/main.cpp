#include "Arduino.h"
#include "config.hpp"
#include "rom.hpp"

void setup() {
    pinMode(BTN_NEXT_ROM_PIN, INPUT_PULLUP);

    set_log_level(LogLevel::INFO);

    
}

void loop() {
    if (!digitalRead(BTN_NEXT_ROM_PIN)) {
        next_rom();
    }
}