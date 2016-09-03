#include "Event.h"

SDL_Event* Event::mainEvent = NULL;

Event::Event() {}

Event::~Event() {}

SDL_Event* Event::getEvent()
{
    if(mainEvent == NULL)
        mainEvent = new SDL_Event();
    return mainEvent;
}