#pragma once
#ifndef GAME_SCREEN
#define GAME_SCREEN

//#include "Tilemap.h"
class Tilemap;
class GameScreen {
public:
    GameScreen();
    ~GameScreen();

    Tilemap* map;

    void Update(float delta);
    void Draw();
};

#endif