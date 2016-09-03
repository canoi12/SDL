#include "Keyboard.h"

const Uint8* Keyboard::keyArray = SDL_GetKeyboardState(NULL);
Keyboard* Keyboard::instance = NULL;

Keyboard::Keyboard(){}

bool Keyboard::keyDown(const char *key)
{
    if (keyArray[SDL_GetScancodeFromName(key)]){
        return true;
    }
    return false;
}

bool Keyboard::keyUp(const char *key)
{
    if (keyArray[SDL_GetScancodeFromName(key)]){
        return false;
    }
    return true;
}

Keyboard* Keyboard::getKeyboard(){
    keyArray = SDL_GetKeyboardState(NULL);
    if (instance == NULL)
        instance = new Keyboard();
    return instance;
}