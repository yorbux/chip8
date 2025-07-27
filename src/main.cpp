#include "Arduino.h"

#include "logger.hpp"
#include "keyboard.hpp"
#include "sound.hpp"
#include "rom.hpp"
#include "chip8.hpp"
#include "U8g2lib.h"

#define BTN_NEXT_ROM_PIN GPIO_NUM_5

void setup() {
    /// coloca el pin del boton una resistencia pull-up interna
    pinMode(BTN_NEXT_ROM_PIN, INPUT_PULLUP);

    /// coloca el logger en modo de info
    set_log_level(LogLevel::INFO);

    /// llama a la funcion principal del chip que inicializa todos los parametros necesarios
    chip8_init(roms[0]);
}

void loop() {
    /// verifica si el boton es presionado para cambiar de ROM (juego)
    if (!digitalRead(BTN_NEXT_ROM_PIN)) {
        next_rom();
    }

    /// chip que corre el chip8
    chip8_run();
}