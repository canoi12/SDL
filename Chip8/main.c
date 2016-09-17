#include "chip8.h"

Chip8 chip = {
    .init = initialize,
    .emulateCycle = emulateCycle,
    .loadGame = loadGame
};

SDL_Window* window;
SDL_Renderer* render;
SDL_Event event;

float FPS = 200;

void drawGraphics(Chip8* c) {
    char ch = 0;
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (c->gfx[(y*64)+x] == 0) {
                SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
                ch = 0;
            }
            else {
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                ch = 1;
            }
            SDL_Rect rect;
            rect.x = x*8;
            rect.y = y*8;
            rect.w = 8;
            rect.h = 8;
            SDL_RenderFillRect(render, &rect);
            //printf("%i ", ch);
        }
        //printf("\n");
    }
}

void updateKeyState() {
    if (keyArray[SDL_SCANCODE_ESCAPE])
        exit(0);

    chip.key[0x1] = keyArray[SDL_SCANCODE_1];
    chip.key[0x2] = keyArray[SDL_SCANCODE_2];
    chip.key[0x3] = keyArray[SDL_SCANCODE_3];
    chip.key[0xC] = keyArray[SDL_SCANCODE_4];

    chip.key[0x4] = keyArray[SDL_SCANCODE_Q];
    chip.key[0x5] = keyArray[SDL_SCANCODE_W];
    chip.key[0x6] = keyArray[SDL_SCANCODE_E];
    chip.key[0xD] = keyArray[SDL_SCANCODE_R];

    chip.key[0x7] = keyArray[SDL_SCANCODE_A];
    chip.key[0x8] = keyArray[SDL_SCANCODE_S];
    chip.key[0x9] = keyArray[SDL_SCANCODE_D];
    chip.key[0xE] = keyArray[SDL_SCANCODE_F];

    chip.key[0xA] = keyArray[SDL_SCANCODE_Z];
    chip.key[0x0] = keyArray[SDL_SCANCODE_X];
    chip.key[0xB] = keyArray[SDL_SCANCODE_C];
    chip.key[0xF] = keyArray[SDL_SCANCODE_V];
}

int main(int argc, char **argv) {
    keyArray = SDL_GetKeyboardState(NULL);
    chip.init(&chip);
    chip.loadGame(&chip, argv[1]);

    window = SDL_CreateWindow("CHIP8 Emulator!", 0, 0, 640, 320, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    float timeCheck = 0;

    Chip8* test = malloc(sizeof(Chip8));
    test->I = 0;

    while(event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);
        chip.emulateCycle(&chip);

        if (chip.drawFlag) {
            SDL_RenderClear(render);
            drawGraphics(&chip);
        }
        updateKeyState();
        SDL_RenderPresent(render);

        chip.drawFlag = 0;

        timeCheck = SDL_GetTicks();

        if (1000/FPS > SDL_GetTicks()-timeCheck) {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-timeCheck));
        }
    }

    return 0;
}