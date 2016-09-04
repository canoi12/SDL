#pragma once
#ifndef PLAYER
#define PLAYER

#include "GameObject.h"
#include "Utils.h"
#include "Keyboard.h"

class Tilemap;
class Player : public GameObject
{
public:
    Player(std::string img_path, float x, float y);
    Player();
    ~Player();

    void Update(float delta);
    void Draw();

    bool collision(GameObject* obj2);

private:
    bool isGround;

    bool col_down;
    bool col_up;
};

#endif