#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"

class CMain
{
public:
    CMain(int passed_ScreenWidth, int passed_ScreenHeight);
    ~CMain(void);

    void GameLoop();

private:
    int ScreenWidth;
    int ScreenHeight;
    bool quit;
    CSprite* sky;
    CSprite* warrior;

    CSDL_Setup* csdl_setup;

    bool moveRight;
    bool moveLeft;
    bool moveUp;
    bool moveDown;

    long timeCheck;
    const int FPS = 60.0f;
    const int TICKS_PER_FRAME = 1000 / FPS;

    MainCharacter* player;

};