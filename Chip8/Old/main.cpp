#include <iostream>
#include <SDL2/SDL.h>
#include "includes/chip8.h"


SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

Chip8 myChip8;

void loadGame(Chip8* c, const char* name);

int main(int argc, char **argv) {
    myChip8.initialize();
    loadGame(&myChip8, argv[1]);

    window = NULL;
    window = SDL_CreateWindow("Chip8 Emulator!", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                quit = true;
        }
        myChip8.emulateCycle();

        SDL_RenderPresent(renderer);
    }

}

void loadGame(Chip8* c, const char* name) {
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
        for (int i = 0; i < lSize; ++i) {
            c->memory[i + 512] = buffer[i];
        }
    } else 
        printf("Error: ROM too big for memory");

    fclose(pFile);
    free(buffer);
}