#pragma once

#include "GameObject.h"
#include "Camera.h"

class Enemy : public GameObject
{
public:
    Enemy(std::string img_path);
    Enemy();
    ~Enemy();

    void Update(float delta);
    void Draw();

    int teste = 1;
};