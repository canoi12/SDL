#pragma once
#ifndef UTILS
#define UTILS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Event.h"
#include "Player.h"
#include "Keyboard.h"
#include "Enemy.h"
#include "Camera.h"
#include "GameScreen.h"
#include "ScreenManager.h"
#include <iostream>
#include <vector>
#include <tinyxml.h>
#include <map>

#include <sstream>

class Tilemap;

class Utils {
public:
    static bool check_solid(int x, int y, Tilemap* map);

    static int CharToInt(const char* value)
    {
        std::stringstream strValue;
        strValue << value;
        int int_value;
        strValue >> int_value;

        return int_value;
    }
};
#endif