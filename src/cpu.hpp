#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>

#include "chip8.hpp"
#include "cpu.hpp"

extern Cpu cpu;

//void cpu_init();
void fetch();
void decode();
void execute();
void deinit();

#endif