#pragma once
#ifndef CHIP8_H
#define CHIP8_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Chip8 {
public:
    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16];

    unsigned short I;
    unsigned short pc;

    unsigned char gfx[64 * 32];

    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned short stack[16];
    unsigned short sp;

    unsigned char key[16];

    bool drawFlag;
public:
    Chip8();
    ~Chip8();
    void initialize();
    void emulateCycle();

};

#endif // !CHIP8_H