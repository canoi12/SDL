#pragma once

#include <SDL2/SDL.h>

class Keyboard 
{
public:
    static Keyboard* instance;

    static bool keyDown(const char *key);
    static bool keyUp(const char *key);

    static Keyboard* getKeyboard();

private:
    Keyboard();
    static const Uint8 *keyArray;
};