#pragma once

#include "Sprite.h"
#include "SDL_Setup.h"

class MainCharacter
{
public:
    MainCharacter(CSDL_Setup* passed_SDL_Setup);
    ~MainCharacter(void);

    void Update(float delta);
    void Draw();

private:
    CSprite* warrior;

    CSDL_Setup* csdl_setup;

    int timeCheck;

    float dx;
    float dy;

    float friction;
    float gravity;

    float xscale;
    float yscale;

    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
};