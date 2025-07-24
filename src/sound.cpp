// sound.c
#include "Arduino.h"
#include "sound.hpp"
#include "logger.hpp"  // Asegúrate de tener una versión en C o wrappers para tu logger


void EspSound_init() {
    pinMode(15, OUTPUT);
    log("Sound ready", LogLevel::INFO);  // Usa una versión C de logger si es necesario
}

void EspSound_deinit() {
    // Si hay algo que limpiar, agrégalo aquí
}

void EspSound_playTune() {
    ledcAttachPin(15, 4);
    ledcWriteTone(4, 500);
}

void EspSound_pauseTune() {
    ledcDetachPin(15);
}
