// sound.h
#ifndef SOUND_H
#define SOUND_H

#include <cstdint>

typedef struct {
    uint16_t pin;
    uint8_t channel;
    uint32_t freq;
} EspSound;

void EspSound_init();
void EspSound_deinit();
void EspSound_playTune();
void EspSound_pauseTune();

#endif
