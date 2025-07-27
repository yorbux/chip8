#include <iostream>
#include <chrono>


#include "chip8.hpp"
#include "cpu.hpp"
#include "rom.hpp"
#include "display.hpp"
#include "sound.hpp"
#include "keyboard.hpp"

using namespace std;

Chip8 chip8;
Cpu cpu;

void cpu_init() {
    cpu.pcreg = 0x200;
    cpu.current_op = 0;
    cpu.sp_reg = 0;
    cpu.ireg = 0;
    cpu.instruction = 0;
    
    // limpia los registros o inicializa en cero
    for (auto i = 0; i < 16; i++) {
        cpu.reg[i] = 0;
    }

    // inicializa el generador random
    srand(time(0));
}

void chip8_init(string rom_path) {
    chip8.cpu = &cpu;
    chip8.cpu->machine = &chip8;

    // Clear frame buffer
    for(auto i = 0; i < SCREEN_HEIGHT; i++)
        for(auto j = 0; j < SCREEN_WIDTH; j++)
            chip8.screen[i][j] = 0;

    // Clear stack
    for(auto i = 0; i < STACK_SIZE; i++)
        chip8.stack[i] = 0;

    // Clear RAM
    for(auto i = 0; i < MEMORY; i++)
        chip8.memory[i] = 0;

    // Load font set into memory
    for(auto i = 0; i < FONTSET_SIZE; i++)
        chip8.memory[i] = FONTSET[i];

    // Reset timers
    chip8.delay_timer = 0;
    chip8.sound_timer = 0;

    // Start keyboard state as all unpressed
    for (auto i = 0; i < NUM_KEYS; i++)
        chip8.keys[i] = 0;

    chip8.key_pressed = false;
    chip8.emulator_running = true;

    // Init cpu registers
    cpu_init();
    
    // Load ROM to the ram
    load_rom(rom_path, chip8.memory+PROGRAM_START_ADDR);
    //for (int i = 0; i < 16; i++) {
    //    printf("%02X ", chip8.memory[0x200 + i]);
    //}
    //printf("\n");


    // Initialize display lib
    d_init();

    s_init();

    k_init();
}

void chip8_run() {
    if (!chip8.emulator_running) {
        return;
    }

    using clock = chrono::high_resolution_clock;
    clock::time_point start = clock::now(), end;

    // funciones de la cpu
    fetch();
    decode();
    //log("Fetched opcode: 0x" + to_hex(chip8.cpu->current_op), LogLevel::DEBUG);
    execute();

    k_update(chip8.keys, &chip8.emulator_running);

    if (chip8.tick_counter >= 20) {
        chip8.tick_counter = 0;
        d_draw(chip8.screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        d_update();

        if (chip8.delay_timer > 0) {
            chip8.delay_timer--;
        }

        if (chip8.sound_timer > 0) {
            chip8.sound_timer--;
            s_playTune();
        } else {
            s_pauseTune();
        }
    }

    chip8.tick_counter++;
    end = clock::now();

    int64_t t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    int64_t sleep_time = 100 - t;
    if (sleep_time > 0) {
        delayMicroseconds(sleep_time);
    }
}