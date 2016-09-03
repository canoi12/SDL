#include "Renderer.h"

Renderer* Renderer::instance = NULL;
SDL_Renderer* Renderer::renderer = NULL;
SDL_Window* Renderer::window = NULL;


Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

SDL_Window* Renderer::getWindow()
{
    return window;
}

void Renderer::setWindow(SDL_Window* passed_window)
{
    window = passed_window;
}

Renderer* Renderer::getInstance()
{
    if (instance == NULL)
    {
        instance = new Renderer();
    }

    return instance;
}

SDL_Renderer* Renderer::getRenderer()
{
    if (renderer == NULL)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    return renderer;
}