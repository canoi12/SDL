#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include "Event.h"
#include "Camera.h"
#include <iostream>


class GameObject
{
public:
    GameObject(std::string img_path, float x, float y);
    GameObject();
    ~GameObject();

    virtual void setQuad(int x, int y, int w, int h);
    virtual void playAnimation(int beginFrame, int endFrame, int row, float speed);

    void setX(float X);
    void setY(float Y);

    int getX();
    int getY();

    int getCenterX();
    int getCenterY();

    int getWidth();
    int getHeight();

    virtual bool collision(GameObject* obj2);

    virtual void Update(float delta);
    virtual void Draw();

protected:
    SDL_Texture* image;
    SDL_Rect rect;
    SDL_Rect crop;

    float x;
    float y;

    float dx;
    float dy;

    int width;
    int height;

    float xscale;
    float yscale;

    float oxscale;

    float bounce;

    int currentFrame;
    float currentTime = 0.f;

    SDL_Point origin;
    SDL_RendererFlip flip;
};