#include <stdio.h>
#include <SDL2/SDL.h>

// Chip 8 emulator, made following the Multigesture tutorial (www.multigesture.net)

static const Uint8 *keyArray;

typedef struct Chip8 {
    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16];

    unsigned short I;
    unsigned short pc;

    unsigned char gfx[64*32];

    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned short stack[16];
    unsigned short sp;

    unsigned char key[16];

    unsigned short drawFlag;
} chip8;

unsigned char chip8_fontset[80] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

// Memory organization
// 0x000 - 0x1FF - Chip 8 interpreter (contains font set in emu)
// 0x050 - 0x0A0 - Used for built in 4x5 pixel font set (0 - F)
// 0x200 - 0xFFF - Program ROM and work RAM

// Initialize the chip 8 variables
void initialize(chip8* c);

// Load the chip 8 game
void loadGame(chip8* c, const char* name);

// Run the chip 8 cycle
void emulateCycle(chip8* c);

void setKeys(chip8 c);

chip8 myChip8;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

void setupGraphics() {
    window = SDL_CreateWindow("Hello World", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void updateKeyState();
void drawGraphics(chip8 *c);

void lerarqui_teste(const char* name) {
    FILE *f;
    printf("%s\n",name);
    f = fopen(name, "rb");

    char ch;
    int i = 0;

    while((ch=fgetc(f))!=EOF) {
        //if (ch >= 48 && ch <= 57 || ch >= 65 && ch <= 70)
            printf("0x%X\n",ch);
        //myChip8.memory[i + 512] = ch;
        //i++;
        //putchar(ch);
    }
    fclose(f);
    //exit(0);
}

int main(int argc, char **argv) {
    keyArray = SDL_GetKeyboardState(NULL);
    setupGraphics();
    //setupInput();

    initialize(&myChip8);
    loadGame(&myChip8, argv[1]);
    lerarqui_teste(argv[1]);

    short quit = 1;

    float timeCheck = 0.0f;
    float FPS = 500;

    printf("Entrando no loop...\n");

    while(quit) {

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                quit = 0;
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);
        emulateCycle(&myChip8);

        if (myChip8.drawFlag) {
            
            SDL_RenderClear(renderer);
            drawGraphics(&myChip8);
        }
        setKeys(myChip8);
        updateKeyState();
        SDL_RenderPresent(renderer);

        myChip8.drawFlag = 0;

        timeCheck = SDL_GetTicks();

        if (1000/FPS > SDL_GetTicks()-timeCheck) {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-timeCheck));
        }
    }

    return 0;
}

void initialize(chip8* c) {
    c->pc = 0x200; // Program counter starts at 0x200;
    c->opcode = 0; // Reset current opcode;
    c->I = 0; // Reset index register;
    c->sp = 0; // Reset stack pointer;

    // Clear display;
    for (int i = 0; i < 64*32; i ++)
        c->gfx[i] = 0;
    
    // Clear stack
    for (int i = 0; i < 16; i++)
        c->stack[i] = 0;

    // Clear registers V0 - VF
    for (int i = 0; i < 16; i++)
        c->V[i] = 0;

    // Clear memory
    for (int i = 0; i < 4096; i++)
        c->memory[i] = 0;
    
    // Load fontsets
    for (int i = 0; i < 80; i++)
        c->memory[i] = chip8_fontset[i];

    for (int i = 0; i < 16; i++)
        c->key[i] = 0;
    
    c->delay_timer = 0;
    c->sound_timer = 0;
}

void emulateCycle (chip8* c) {

    // Fetch opcode
    c->opcode = c->memory[c->pc] << 8 | c->memory[c->pc + 1];

    unsigned short x = (c->opcode & 0x0F00) >> 8;
    unsigned short y = (c->opcode & 0x00F0) >> 4;

    //printf("0x%X\n",c->opcode);
    // Decode opcode
    switch (c->opcode & 0xF000)
    {
        case 0x0000:
            //printf("teste");
            switch(c->opcode & 0x000F) {
                case 0x0000: // 00E0: Clears the screen
                    for ( int i = 0; i < 2048; i++)
                        c->gfx[i] = 0x0;
                    c->drawFlag = 1;
                    c->pc += 2;
                break;

                case 0x000E: // 00EE: Returns from a subroutine
                    if (c->sp > 0)
                        c->sp--;
                    c->pc = c->stack[c->sp];
                    c->pc += 2;
                break;

                default:
                    printf("Unknown opcode: 0x%X\n", c->opcode);
                    c->pc += 2;
                    break;
            }
            break;
        case 0x1000: // 1NNN: Jumps to address NNN
            c->pc = c->opcode & 0x0FFF;
            break;
        case 0x2000: // 2NNN: Calls subroutine at NNN
            c->stack[c->sp] = c->pc;
            c->sp++;
            c->pc = c->opcode & 0x0FFF;
            break;
        case 0x3000: // 3XNN: Skips the next instruction if VX equals NN
            if (c->V[(c->opcode & 0x0F00) >> 8] == (c->opcode & 0x00FF))
                c->pc += 4;
            else
                c->pc += 2;
            break;
        case 0x4000: // 4XNN: Skips the next instruction if VX doesn't equals NN
            if (c->V[(c->opcode & 0x0F00) >> 8] != (c->opcode & 0x00FF))
                c->pc += 4;
            else
                c->pc += 2;
            break;
        case 0x5000: // 5XY0: Skips the next instruction if VX equals VY
            if (c->V[(c->opcode & 0x0F00) >> 8] == c->V[(c->opcode & 0x00F0) >> 4])
                c->pc += 4;
            else
                c->pc += 2;
            break;
        case 0x6000: // 6XNN: Sets VX to NN
            c->V[(c->opcode & 0x0F00) >> 8] = c->opcode & 0x00FF;
            c->pc += 2;
            break;
        case 0x7000: // 7XNN: Adds NN to VX
            c->V[(c->opcode & 0x0F00) >> 8] += c->opcode & 0x00FF;
            c->pc += 2;
            break;
        case 0x8000: // Subcodes
            switch(c->opcode & 0x000F) {
                case 0x0000: // 8XY0: Sets VX to the value of VY
                    c->V[(c->opcode & 0x0F00) >> 8] = c->V[(c->opcode & 0x00F0) >> 4];
                    c->pc += 2;
                    break;
                case 0x0001: // 8XY1: Sets VX to VX or VY
                    c->V[(c->opcode & 0x0F00) >> 8] = c->V[(c->opcode & 0x0F00) >> 8] | c->V[(c->opcode & 0x00F0) >> 4];
                    c->pc += 2;
                    break;
                case 0x0002: // 8XY2: Sets VX to VX and VY
                    c->V[(c->opcode & 0x0F00) >> 8] = c->V[(c->opcode & 0x0F00) >> 8] & c->V[(c->opcode & 0x00F0) >> 4];
                    c->pc += 2;
                    break;
                case 0x00003: // 8XY3: Sets VX to VY xor VY
                    c->V[(c->opcode & 0x0F00) >> 8] = c->V[(c->opcode & 0x0F00) >> 8] ^ c->V[(c->opcode & 0x00F0) >> 4];
                    c->pc += 2;
                    break;
                case 0x0004: // 8XY4: Ads VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
                    if (c->V[(c->opcode & 0x00F0) >> 4] > (0xFF - c->V[(c->opcode & 0x0F00) >> 8]))
                        c->V[0xF] = 1; // carry
                    else
                        c->V[0xF] = 0;
                    c->V[(c->opcode & 0x0F00) >> 8] += c->V[(c->opcode & 0x00F0) >> 4];
                    c->pc += 2;
                    break;
                case 0x0005: // 8XY5: VY is subtracted from VX VF is set to 0 when there's a borrow, and 1 when there isn't
                    if (c->V[(c->opcode & 0x00F0) >> 4] > (c->V[(c->opcode & 0x0F00) >> 8]))
                        c->V[0xF] = 0; // borrow
                    else
                        c->V[0xF] = 1;
                    c->V[(c->opcode & 0x0F00) >> 8] -= c->V[(c->opcode & 0x00F0) >> 4];
                    c->pc += 2;
                    break;
                case 0x0006: // 8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift
                    c->V[0xF] = c->V[(c->opcode & 0x0F00) >> 8] & 0x1;
                    c->V[(c->opcode & 0x0F00) >> 8] >>= 1;
                    c->pc += 2;
                    break;
                case 0x0007: // 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
                    if (c->V[(c->opcode & 0x0F00) >> 8] > (c->V[(c->opcode & 0x00F0) >> 4]))
                        c->V[0xF] = 0; // borrow
                    else
                        c->V[0xF] = 1;

                    c->V[(c->opcode & 0x0F00) >> 8] = c->V[(c->opcode & 0x00F0) >> 4] - c->V[(c->opcode & 0x0F00) >> 8];
                    c->pc += 2;
                    break;
                case 0x000E: // 8XYE: Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
                    c->V[0xF] = c->V[(c->opcode & 0x0F00) >> 8] >> 7;
                    c->V[(c->opcode & 0x0F00) >> 8] <<= 1;
                    c->pc += 2;
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", c->opcode);
                    c->pc += 2;
                    break;
            }
            break;
        case 0x9000: // 9XY0: Skips the next instruction if VX doesn't equal VY
            if (c->V[(c->opcode & 0x0F00) >> 8] != c->V[(c->opcode & 0x00F0) >> 4])
                c->pc += 4;
            else
                c->pc += 2;
            break;
        case 0xA000: // ANNN: Sets I to the address NNN
            // Execute opcode
            c->I = c->opcode & 0x0FFF;
            c->pc += 2;
            break;
        case 0xB000: // BNNN: Jumps to the address NNN plus V0
            c->pc = (c->opcode & 0x0FFF) + c->V[0];
            break;
        case 0xC000: // CXNN: Sets VX to the result of a bitwise and operation on a random number and NN
            c->V[(c->opcode & 0x0F00) >> 8] = (rand()%0xFF) & (c->opcode & 0x00FF);
            c->pc += 2;
            break;
        case 0xD000: {/* DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1               if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen*/
            /*unsigned short x = c->V[(c->opcode & 0x0F00) >> 8];
            unsigned short y = c->V[(c->opcode & 0x00F0) >> 4];
            unsigned short height = c->opcode & 0x000F;
            unsigned short pixel;

            unsigned short dx, dy;

            c->V[0xF] = 0;
            for (int yline = 0; yline < height; yline++) {
                pixel = c->memory[c->I + yline];
                for (int xline = 0; xline < 8; xline++) {
                    dx = x + xline;
                    dy = y + yline;
                    if ((pixel & (0x80 >> xline)) != 0) {
                        if (dx > 64) 
                            dx -= 64;
                        else if (dx < 0)
                            dx += 64;

                        if (dy > 32)
                            dy -= 32;
                        else if (dy < 0)
                            dy += 32;
                        if (c->gfx[(dx + ((dy) * 64))] == 1)
                            c->V[0xF] = 1;
                        c->gfx[dx + ((dy) * 64)] ^= 1;
                    }
                }

                c->drawFlag = 1;
                c->pc += 2;*/
                unsigned short x = c->V[(c->opcode & 0x0F00) >> 8];
                unsigned short y = c->V[(c->opcode & 0x00F0) >> 4];
                unsigned short height = c->opcode & 0x000F;
                unsigned short pixel;
                
                c->V[0xF] = 0;
                for (int yline = 0; yline < height; yline++)
                {
                    pixel = c->memory[c->I + yline];
                    for(int xline = 0; xline < 8; xline++)
                    {
                        if((pixel & (0x80 >> xline)) != 0)
                        {
                            if(c->gfx[(x + xline + ((y + yline) * 64))] == 1)
                                c->V[0xF] = 1;                                 
                            c->gfx[x + xline + ((y + yline) * 64)] ^= 1;
                        }
                    }
                }
                
                c->drawFlag = 1;
                c->pc += 2;
            }
            break;
        case 0xE000: 
            switch(c->opcode & 0x000F) {
                case 0x000E: // EX9E: Skips the next instruction if the key stored in VX is pressed
                    if (c->key[c->V[(c->opcode & 0x0F00) >> 8]] != 0)
                        c->pc += 4;
                    else
                        c->pc += 2;

                    break;
                case 0x0001: // EXA1: Skips the next instruction if the key stored in VX isn't pressed
                    if (c->key[c->V[(c->opcode & 0x0F00) >> 8]] == 0)
                        c->pc += 4;
                    else
                        c->pc += 2;
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", c->opcode);
                    c->pc += 2;
                    break;
            }
            break;
        case 0xF000:
            switch (c->opcode & 0x000F) {
                case 0x0007: // FX07: Sets the delay timer to VX
                    c->V[(c->opcode & 0x0F00) >> 8] = c->delay_timer;
                    c->pc += 2;
                    break;
                case 0x000A: // FX0A: A key press is awaited, and then stored in VX.
                    {   
                        short keyPress = 0;
                        for (int i = 0; i < 16; i++) {
                            if (c->key[i] != 0) {
                                c->V[(c->opcode & 0x0F00) >> 8] = i;
                                keyPress = 1;
                            }
                        }
                        if (!keyPress)
                            return;
                        c->pc += 2;
                    }
                    break;
                case 0x0005: 
                    switch(c->opcode & 0x00F0) {
                        case 0x0010: // FX15: Sets the delay timer to VX.
                            c->delay_timer = c->V[(c->opcode & 0x0F00) >> 8];
                            c->pc += 2;
                            break;
                        case 0x0050: // FX55: Stores V0 to VX (including VX) in memory starting at address I
                            for (int i = 0; i <= ((c->opcode & 0x0F00) >> 8); i++) 
                                c->memory[c->I + i] = c->V[i];
                            c->I += ((c->opcode & 0x0F00) >> 8) + 1;
                            c->pc += 2;
                            break;
                        case 0x0060: // FX65: Fills V0 to VX (including VX) with values from memory starting at address I
                            for (int  i = 0; i <= ((c->opcode & 0x0F00) >> 8); i++)
                                c->V[i] = c->memory[c->I + i];

                            c->I += ((c->opcode & 0x0F00) >> 8) + 1;
                            c->pc += 2;
                            break;
                        default:
                            printf("Unknown opcode: 0x%X\n", c->opcode);
                            c->pc += 2;
                            break;
                    }
                    break;
                case 0x0008: // FX18: Sets the sound timer to VX.
                    c->sound_timer = c->V[(c->opcode & 0x0F00) >> 8];
                    c->pc += 2;
                    break;
                case 0x000E: // FX1E: Adds VX to I
                    if (c->I + c->V[(c->opcode & 0x0F00) >> 8] > 0xFFF) 
                        c->V[0xF] = 1;
                    else
                        c->V[0xF] = 0;
                    c->I += c->V[(c->opcode & 0x0F00) >> 8];
                    c->pc += 2;
                    break;
                case 0x0009: // FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font
                    c->I = c->V[(c->opcode & 0x0F00) >> 8] * 0x5;
                    c->pc += 2;
                    break;
                case 0x0003: // FX33: Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the                     hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
                    c->memory[c->I]     = c->V[(c->opcode & 0x0F00) >> 8] / 100;
                    c->memory[c->I + 1] = (c->V[(c->opcode & 0x0F00) >> 8] / 10) % 10;
                    c->memory[c->I + 2] = (c->V[(c->opcode & 0x0F00) >> 8] % 100) % 10;
                    c->pc += 2;
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", c->opcode);
                    c->pc += 2;
                    break;
            }
            break;
        default:
            printf("Unknown opcode: 0x%X\n", c->opcode);
            c->pc += 2;
            break;
    }

    if (c->delay_timer > 0)
        --c->delay_timer;
    if (c->sound_timer > 0)
    {
        if (c->sound_timer == 1)
            printf("BEEP!\n");
        --c->sound_timer;
    }

}

void loadGame(chip8* c, const char* name) {
    FILE* pFile;
    pFile = fopen(name, "rb");
    if (pFile == NULL)
        printf("File error");

    fseek(pFile, 0, SEEK_END);
    long lSize = ftell(pFile);
    rewind(pFile);
    printf("Filesize: %d\n", (int)lSize);

    char * buffer = (char*)malloc(sizeof(char) * lSize);
    if (buffer == NULL)
        printf("Memory error");
    
    size_t result = fread (buffer, 1, lSize, pFile);
    if (result != lSize)
        printf("Reading error");
    
    printf("0x%X\n",buffer[4]);
    if ((4096-512) > lSize)
    {
        for (int i = 0; i < lSize; i++) {
            c->memory[i + 512] = buffer[i];
        }
    } else 
        printf("Error: ROM too big for memory");

    fclose(pFile);
    free(buffer);
}

void setKeys(chip8 c) {

}

void drawGraphics(chip8* c) {
    char ch = 0;
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (c->gfx[(y*64)+x] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                ch = 0;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                ch = 1;
            }
            SDL_Rect rect;
            rect.x = x*8;
            rect.y = y*8;
            rect.w = 8;
            rect.h = 8;
            SDL_RenderFillRect(renderer, &rect);
            //printf("%i ", ch);
        }
        //printf("\n");
    }
}

void updateKeyState() {
    if (keyArray[SDL_SCANCODE_ESCAPE])
        exit(0);

    myChip8.key[0x1] = keyArray[SDL_SCANCODE_1];
    myChip8.key[0x2] = keyArray[SDL_SCANCODE_2];
    myChip8.key[0x3] = keyArray[SDL_SCANCODE_3];
    myChip8.key[0xC] = keyArray[SDL_SCANCODE_4];

    myChip8.key[0x4] = keyArray[SDL_SCANCODE_Q];
    myChip8.key[0x5] = keyArray[SDL_SCANCODE_W];
    myChip8.key[0x6] = keyArray[SDL_SCANCODE_E];
    myChip8.key[0xD] = keyArray[SDL_SCANCODE_R];

    myChip8.key[0x7] = keyArray[SDL_SCANCODE_A];
    myChip8.key[0x8] = keyArray[SDL_SCANCODE_S];
    myChip8.key[0x9] = keyArray[SDL_SCANCODE_D];
    myChip8.key[0xE] = keyArray[SDL_SCANCODE_F];

    myChip8.key[0xA] = keyArray[SDL_SCANCODE_Z];
    myChip8.key[0x0] = keyArray[SDL_SCANCODE_X];
    myChip8.key[0xB] = keyArray[SDL_SCANCODE_C];
    myChip8.key[0xF] = keyArray[SDL_SCANCODE_V];
}