#include "config.hpp"
#include "logger.hpp"

void next_rom(void) {
    // sizeof(roms) -> calcula el tamano en bytes del arreglo
    // sizeof(*roms) -> calcula el tamano de un solo elemento del arreglo
    // al dividir da el valor total de elementos del arreglo
    if (c_rom >= sizeof(roms) / sizeof(*roms)) {
        c_rom = 0;
    }

    log("Cambiando rom a: " + roms[c_rom], LogLevel::WARN);
    
    c_rom++;
}