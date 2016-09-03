#pragma once

#include "GameObject.h"
#include "Camera.h"

class Enemy : public GameObject
{
public:
    Enemy(std::string img_path, float x, float y);
    Enemy();
    ~Enemy();

    void Update(float delta);
    void Draw();
};