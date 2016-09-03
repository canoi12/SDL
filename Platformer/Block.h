#pragma once

#include "GameObject.h"

class Block : public GameObject
{
public:
    Block();
    Block(std::string img_path, float x, float y);
    ~Block();

    void Update(float delta);
    void Draw();
};