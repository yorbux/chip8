// sound.c
#include "Arduino.h"
#include "sound.hpp"
#include "logger.hpp"

void s_init() {
    pinMode(15, OUTPUT);
    log("Sound ready", LogLevel::INFO);
}

void s_playTune() {
    ledcAttachPin(15, 4);
    ledcWriteTone(4, 500);
}

void s_pauseTune() {
    ledcDetachPin(15);
}
