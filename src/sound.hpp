// sound.h
#ifndef SOUND_H
#define SOUND_H

#include <cstdint>

/// @brief Coloca el buzzer que esta conectado al pin 15 del esp32 en modo OUTPUT
void s_init();
/// @brief define el canal que va a usar el buzzer en este caso 4 y la frecuencia del buzzer que es 500.
void s_playTune();
/// @brief pausa el tono del buzzer
void s_pauseTune();

#endif
