#include "config.hpp"
#include "logger.hpp"
#include "roms.h"

using namespace std;



void load_rom(string& file_path, uint8_t* mem) {
    log("Loading ROM: " + file_path, LogLevel::INFO);

    const uint8_t* pointer = nullptr;
    uint32_t size = 0;

    switch (file_path[0]) {
        // set pointer and size
        case 'b': 
            pointer = rom_Breakout1; 
            size = rom_Breakout1_size; 
            break;
        case 'p': 
            pointer = rom_Pong1; 
            size = rom_Pong1_size; 
            break;
        case 'm': 
            pointer = rom_Maze1; 
            size = rom_Maze1_size; 
            break;
    }

    if (pointer == nullptr || size == 0 || size > (0xFFF - 0x200)) {
        log("No se puede cargar la ROM", LogLevel::ERROR);
        return;
    }

    for (uint32_t i = 0; i < size; i++) {
        mem[i] = pgm_read_byte(&(pointer[i]));
    }
    log("Rom cargada", LogLevel::INFO);
}

void next_rom(void) {
    // sizeof(roms) -> calcula el tamano en bytes del arreglo
    // sizeof(*roms) -> calcula el tamano de un solo elemento del arreglo
    // al dividir da el valor total de elementos del arreglo
    if (c_rom >= sizeof(roms) / sizeof(*roms)) {
        c_rom = 0;
    }

    log("Cambiando rom a: " + roms[c_rom], LogLevel::WARN);
    chip8_init(roms[c_rom]);
    c_rom++;
}