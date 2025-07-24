#include <cstdlib>
#include <ctime>

#include "cpu.hpp"
#include "chip8.hpp"
#include "logger.hpp"

Cpu cpu;



/*****************************
 * 0ZE0
 *****************************/
void clear_screen()
{
    for(int i=0; i<SCREEN_HEIGHT; i++)
        for(int j=0; j<SCREEN_WIDTH; j++)
            cpu.machine->screen[i][j]=0;
}

/*****************************
 * 0ZEE
 *****************************/
void return_from_subroutine()
{
    cpu.sp_reg--;
    cpu.pcreg = cpu.machine->stack[cpu.sp_reg];
}

// Private functions
/*****************************
 * 0ZZZ
 *****************************/
void decode_0_instruction()
{
    switch(cpu.current_op & 0xFF)
    {
        case 0xE0: clear_screen(); break;
        case 0xEE: return_from_subroutine(); break;
        default: log("Instruction 0 with code " + std::to_string(cpu.current_op & 0xFF), LogLevel::ERROR);
    }
}

/*****************************
 * 1NNN
 *****************************/
void jump_to()
{
    cpu.pcreg = cpu.current_op & 0x0FFF;
}

/*****************************
 * 2NNN
 *****************************/
void call_subroutine()
{
    uint16_t nnn = cpu.current_op & 0x0FFF;

    cpu.machine->stack[cpu.sp_reg] = cpu.pcreg;
    cpu.sp_reg++;
    cpu.pcreg = nnn;
}

/*****************************
 * 3XNN
 *****************************/
void skip_next_instruction_eq()
{
    uint8_t value = cpu.current_op & 0xFF;
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    if(cpu.reg[reg] == value)
        cpu.pcreg += 2;
}

/*****************************
 * 4XNN
 *****************************/
void skip_next_instruction_ne()
{
    uint8_t value = cpu.current_op & 0xFF;
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    if(cpu.reg[reg] != value)
        cpu.pcreg += 2;
}

/*****************************
 * 5XYZ
 *****************************/
void skip_next_instruction_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    if(cpu.reg[reg_x] == cpu.reg[reg_y])
        cpu.pcreg += 2;
}

/*****************************
 * 6XNN
 *****************************/
void register_set()
{
    uint8_t value = cpu.current_op & 0xFF;
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    cpu.reg[reg] = value;
}

/*****************************
 * 7XNN
 *****************************/
void add_reg_imm()
{
    uint8_t value = cpu.current_op & 0xFF;
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    cpu.reg[reg] += value;
}


/*****************************
 * 8XY0
 *****************************/
void move_vy_to_vx()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    cpu.reg[reg_x] = cpu.reg[reg_y];
}

/*****************************
 * 8XY1
 *****************************/
void or_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    cpu.reg[reg_x] |= cpu.reg[reg_y];
}

/*****************************
 * 8XY2
 *****************************/
void and_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    cpu.reg[reg_x] &= cpu.reg[reg_y];
}

/*****************************
 * 8XY3
 *****************************/
void xor_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    cpu.reg[reg_x] ^= cpu.reg[reg_y];
}

/*****************************
 * 8XY4
 *****************************/
void add_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;
    uint16_t add = cpu.reg[reg_x] + cpu.reg[reg_y];

    if(add > 0xFF)
        cpu.reg[0xF] = 1;
    else
        cpu.reg[0xF] = 0;

    cpu.reg[reg_x] = add & 0xFF;
}

/*****************************
 * 8XY5
 *****************************/
void sub_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    if(cpu.reg[reg_x] > cpu.reg[reg_y])
        cpu.reg[0xF] = 1;
    else
        cpu.reg[0xF] = 0;

    cpu.reg[reg_x] -= cpu.reg[reg_y];
}

/*****************************
 * 8XY6
 *****************************/
void shift_right_reg()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    if(cpu.reg[reg] % 2 == 1 )
        cpu.reg[0xF] = 1;
    else
        cpu.reg[0xF] = 0;

    cpu.reg[reg] >>= 1;
}

/*****************************
 * 8XY7
 *****************************/
void subn_vx_vy()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    if(cpu.reg[reg_y] > cpu.reg[reg_x])
        cpu.reg[0xF] = 1;
    else
        cpu.reg[0xF] = 0;

    cpu.reg[reg_x] = cpu.reg[reg_y] - cpu.reg[reg_x];
}

/*****************************
 * 8XYE
 *****************************/
void shift_left_reg()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    if(cpu.reg[reg] & 0x80 == 1 )
        cpu.reg[0xF] = 1;
    else
        cpu.reg[0xF] = 0;

    cpu.reg[reg] <<= 1;
}

/*****************************
 * 9XYZ
 *****************************/
void skip_next_instruction_vx_vy_ne()
{
    uint8_t reg_x = (cpu.current_op >> 8) & 0x0F;
    uint8_t reg_y = (cpu.current_op >> 4) & 0x0F;

    if(cpu.reg[reg_x] != cpu.reg[reg_y])
        cpu.pcreg += 2;
}

/*****************************
 * ANNN
 *****************************/
void set_index_register()
{
    cpu.ireg = cpu.current_op & 0x0FFF;
}

/*****************************
 * BNNN
 *****************************/
void jump_with_v0()
{
    uint16_t nnn = cpu.current_op & 0x0FFF;

    cpu.pcreg = nnn + cpu.reg[0];
}

/*****************************
 * CXKK
 *****************************/
void generate_random_number()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    uint8_t kk = cpu.current_op & 0xFF;
    uint8_t randNum = rand() % 256;

    cpu.reg[reg] = randNum & kk;
}

/*****************************
 * DXYN
 *****************************/
void draw_sprite()
{
    uint8_t v_reg_x = (cpu.current_op & 0x0F00) >> 8;
    uint8_t v_reg_y = (cpu.current_op & 0x00F0) >> 4;   
    uint8_t sprite_height = cpu.current_op & 0x000F;
    uint8_t x_location = cpu.reg[v_reg_x];
    uint8_t y_location = cpu.reg[v_reg_y];

    // Reset colision register
    cpu.reg[0xF] = 0;
    for(int y_coordinate = 0; y_coordinate < sprite_height; y_coordinate++)
    {
        uint8_t pixel = cpu.machine->memory[cpu.ireg + y_coordinate];
        for(int x_coordinate = 0; x_coordinate < 8; x_coordinate++)
        {
            if((pixel & (0x80 >> x_coordinate)) != 0)
            { 
                if(cpu.machine->screen[y_location + y_coordinate][x_location + x_coordinate] == 1)
                    cpu.reg[0xF] = 1;
                
                cpu.machine->screen[y_location + y_coordinate][x_location + x_coordinate] ^= 0x1;
            }
        }
    }
}


/*****************************
 * EX9E
 *****************************/
void skip_next_inst_if_key_pressed()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    uint8_t val = cpu.reg[reg];

    if(cpu.machine->keys[val] != 0)
        cpu.pcreg += 2;
}

/*****************************
 * EXA1
 *****************************/
void skip_next_inst_if_not_pressed()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    uint8_t val = cpu.reg[reg];

    if(cpu.machine->keys[val] == 0)
        cpu.pcreg += 2;
}


/*****************************
 * EZZZ
 *****************************/
void decode_E_instruction()
{
    switch(cpu.current_op & 0xFF)
    {
        case 0x009E: skip_next_inst_if_key_pressed(); break;
        case 0x00A1: skip_next_inst_if_not_pressed(); break;
        default: log("Instruction E with code " + std::to_string(cpu.current_op & 0xFF), LogLevel::ERROR);
    }
}


/*****************************
 * FX07
 *****************************/
void load_reg_with_delay_timer()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    cpu.reg[reg] = cpu.machine->delay_timer;
}

/*****************************
 * FX0A
 *****************************/
void wait_key_press()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    bool key_pressed = false;

    for(int i=0; i<NUM_KEYS; i++)
    {
        if(cpu.machine->keys[i] != 0)
        {
            cpu.reg[reg] = i;
            key_pressed = true;
        }
    }

    if(!key_pressed)
        cpu.pcreg -= 2;
}

/*****************************
 * FX15
 *****************************/
void load_delay_timer_with_reg()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    cpu.machine->delay_timer = cpu.reg[reg];
}

/*****************************
 * FX18
 *****************************/
void load_sound_timer_with_reg()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    cpu.machine->sound_timer = cpu.reg[reg];
}

/*****************************
 * FX1E
 *****************************/
void add_ireg_with_reg()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    cpu.ireg += cpu.reg[reg];
}

/*****************************
 * FX29
 *****************************/
void load_font_from_vx()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;
    cpu.ireg = cpu.reg[reg] * 0x5;
}

/*****************************
 * FX33
 *****************************/
void store_binary_code_decimal_representation()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    cpu.machine->memory[cpu.ireg] = cpu.reg[reg] / 100;
    cpu.machine->memory[cpu.ireg+1] = (cpu.reg[reg] / 10) % 10;
    cpu.machine->memory[cpu.ireg+1] = (cpu.reg[reg] % 100) % 10;
}

/*****************************
 * FX55
 *****************************/
void load_memory_from_regs()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    for(int i=0; i<=reg; i++)
        cpu.machine->memory[cpu.ireg + i] = cpu.reg[i];

    cpu.ireg += (reg + 1);
}

/*****************************
 * FX65
 *****************************/
void load_regs_from_memory()
{
    uint8_t reg = (cpu.current_op >> 8) & 0x0F;

    for(int i=0; i<=reg; i++)
        cpu.reg[i] = cpu.machine->memory[cpu.ireg + i];

    cpu.ireg += (reg + 1);
}

/*****************************
 * 8XYZ
 *****************************/
void decode_8_instruction()
{
    switch(cpu.current_op & 0xF)
    {
        case 0x0: move_vy_to_vx(); break;
        case 0x1: or_vx_vy(); break;
        case 0x2: and_vx_vy(); break;
        case 0x3: xor_vx_vy(); break;
        case 0x4: add_vx_vy(); break;
        case 0x5: sub_vx_vy(); break;
        case 0x6: shift_right_reg(); break;
        case 0x7: subn_vx_vy(); break;
        case 0xE: shift_left_reg(); break;
        default: log("Instruction 8 with code " + std::to_string(cpu.current_op & 0xF), LogLevel::ERROR);
    }
}


/*****************************
 * FZZZ
 *****************************/
void decode_F_instruction()
{
    switch(cpu.current_op & 0xFF)
    {
        case 0x0007: load_reg_with_delay_timer(); break;
        case 0x000A: wait_key_press(); break;
        case 0x0015: load_delay_timer_with_reg(); break;
        case 0x0018: load_sound_timer_with_reg(); break;
        case 0x001E: add_ireg_with_reg(); break;
        case 0x0029: load_font_from_vx(); break;
        case 0x0033: store_binary_code_decimal_representation(); break;
        case 0x0055: load_memory_from_regs(); break;
        case 0x0065: load_regs_from_memory(); break;
        default: log("Instruction F with code " + std::to_string(cpu.current_op & 0xFF), LogLevel::ERROR);
    }
}

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

void fetch() {
    cpu.current_op = ((uint16_t)cpu.machine->memory[cpu.pcreg] << 8) | cpu.machine->memory[cpu.pcreg+1];
    cpu.pcreg += 2;
}

void decode() {
    cpu.instruction = cpu.current_op >> 12;
}

void execute() {
    log("INST " + std::to_string(cpu.instruction), LogLevel::DEBUG);

    switch (cpu.instruction) {
        case 0x0: decode_0_instruction(); break;
        case 0x1: jump_to(); break;
        case 0x2: call_subroutine(); break;
        case 0x3: skip_next_instruction_eq(); break;
        case 0x4: skip_next_instruction_ne(); break;
        case 0x5: skip_next_instruction_vx_vy(); break;
        case 0x6: register_set(); break;
        case 0x7: add_reg_imm(); break;
        case 0x8: decode_8_instruction(); break;
        case 0x9: skip_next_instruction_vx_vy_ne(); break;
        case 0xA: set_index_register(); break;
        case 0xB: jump_with_v0(); break;
        case 0xC: generate_random_number(); break;
        case 0xD: draw_sprite(); break;
        case 0xE: decode_E_instruction(); break;
        case 0xF: decode_F_instruction(); break;
        default: log("IMPOSSIBLE INSTRUCTION" + std::to_string(cpu.instruction), LogLevel::ERROR);
    }
}