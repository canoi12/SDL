#pragma once

#include <SDL2/SDL.h>

class Event
{
public:
    static SDL_Event* getEvent();
private:
    Event();
    ~Event();

    static SDL_Event* mainEvent;

};