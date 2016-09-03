#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class CSDL_Setup
{
public:
    CSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight);
    ~CSDL_Setup(void);

    SDL_Renderer* getRenderer();
    SDL_Event* getMainEvent();

    void Begin();
    void End();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* mainEvent;
};