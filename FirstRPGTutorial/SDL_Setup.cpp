#include "SDL_Setup.h"

CSDL_Setup::CSDL_Setup(bool* quit, int ScreenWidth, int ScreenHeight)
{
    window = NULL;
    window = SDL_CreateWindow("My First RPG", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        std::cout << "Window couldn't be created" << std::endl;
        *quit = true;
        //return 0;
    }

    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(renderer, 128, 128);
    
    mainEvent = new SDL_Event();
}

CSDL_Setup::~CSDL_Setup(void)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete mainEvent;
}

SDL_Renderer* CSDL_Setup::getRenderer()
{
    return renderer;
}

SDL_Event* CSDL_Setup::getMainEvent()
{
    return mainEvent;
}

void CSDL_Setup::Begin()
{
    SDL_PollEvent(mainEvent);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

void CSDL_Setup::End()
{
    SDL_RenderPresent(renderer);
}