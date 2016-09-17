#include <stdio.h>
#include <SDL2/SDL.h>

#pragma once
#ifndef CHIP8_H
#define CHIP8_H

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

static const Uint8 *keyArray;

typedef struct chip8 Chip8;

typedef struct chip8 {
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

    unsigned char drawFlag;

    void (*init)(Chip8 *self);
    void (*emulateCycle)(Chip8 *self);
    void (*loadGame)(Chip8 *self, const char* name);
} Chip8;

//extern Chip8;
extern unsigned char chip8_fontset[80];

void initialize(Chip8 *c);
void loadGame(Chip8 *c, const char* name);
void emulateCycle(Chip8 *c);

#endif