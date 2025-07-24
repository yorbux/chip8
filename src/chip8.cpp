#include <iostream>

#include "chip8.hpp"
#include "cpu.hpp"
#include "rom.hpp"

using namespace std;

Chip8 chip8;

void chip8_init(string rom_path) {
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
    
    // Init cpu registers
    cpu_init();
    
    // Load ROM to the ram
    load_rom(rom_path, chip8.memory+PROGRAM_START_ADDR);
    
    // Initialize display lib
    d_init();

    // Initialize sound lib
    //sound_init();
  
    // Initialize keyboard lib
    //keyboard_init();
}

void chip8_run() {
    if (!chip8.emulator_running) {
        return;
    }

    clock::time_point start = clock::now(), end;

    // funciones de la cpu
    fetch();
    decode();
    execute();

    if (chip8.tick_counter >= 20) {
        chip8.tick_counter = 0;
        d_draw(chip8.screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        d_update();

        if (chip8.delay_timer > 0) {
            chip8.delay_timer--;
        }

        if (chip8.sound_timer > 0) {
            chip8.sound_timer--;
            //s_play_tune();
        } else {
            //s_pause_tune();
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

void chip8_set_display(Display display) {
    chip8.display = display;
}