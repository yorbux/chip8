#include "Arduino.h"

#include "config.hpp"
#include "logger.hpp"
#include "keyboard.hpp"
#include "sound.hpp"
#include "rom.hpp"
#include "chip8.hpp"
#include "U8g2lib.h"

void setup() {

    pinMode(BTN_NEXT_ROM_PIN, INPUT_PULLUP);

    set_log_level(LogLevel::INFO);

    chip8_set_display(&display);
    chip8_init(roms[0]);
}

void loop() {
    if (!digitalRead(BTN_NEXT_ROM_PIN)) {
        next_rom();
    }

    chip8_run();
}