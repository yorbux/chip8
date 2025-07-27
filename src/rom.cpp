#include "logger.hpp"
#include "chip8.hpp"
#include "rom.hpp"
#include "roms.h"

using namespace std;

std::string roms[] = {"l", "b", "p", "t"};
u_int8_t c_rom = 1;

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
        case 't': 
            pointer = tetris; 
            size = tetris_size; 
            break;
        case 'l':
            pointer = ibm_logo;
            size = ibm_logo_size;
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