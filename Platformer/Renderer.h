#pragma once


#include <SDL2/SDL.h>

class Renderer
{
public:
    static Renderer* getInstance();
    static SDL_Renderer* getRenderer();
    static void setWindow(SDL_Window* passed_window);
    static SDL_Window* getWindow();

private:
    Renderer();
    ~Renderer();
    static SDL_Renderer* renderer;
    static Renderer* instance;
    static SDL_Window* window;
};