#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>

#include "chip8.hpp"

typedef struct {
    uint8_t reg[16];
    uint16_t ireg;
    uint16_t pcreg;
    uint16_t sp_reg;

    uint16_t current_op;
    uint16_t instruction;

    Chip8* machine;
} Cpu;

void cpu_init();
void fetch();
void decode();
void execute();
void deinit();

#endif