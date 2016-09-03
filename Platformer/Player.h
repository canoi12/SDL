#pragma once

#include "GameObject.h"
#include "Keyboard.h"

class Player : public GameObject
{
public:
    Player(std::string img_path);
    Player();
    ~Player();

    void Update(float delta);
    void Draw();

    bool collision(GameObject* obj2);

private:
    bool isGround;
};