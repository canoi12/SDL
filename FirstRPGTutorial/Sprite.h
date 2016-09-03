#pragma once

#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<iostream>

class CSprite
{
public:
    CSprite(SDL_Renderer* passed_renderer, std::string path, int x, int y, int w, int h);
    ~CSprite(void);

    void Draw();

    void setX(float X);
    void setY(float Y);
    void setPosition(float X, float Y);

    float getX();
    float getY();

    int getWidth();
    int getHeight();

    int setWidth(int W);
    int setHeight(int H);

    int getFrameWidth();
    int getFrameHeight();

    void setOrigin(float X, float Y);

    void playAnimation(int beginFrame, int endFrame, int row, float speed);
    void setUpAnimation(int passed_frameWidth, int passed_frameHeight);
private:
    float Origin_X;
    float Origin_Y;

    float X_pos;
    float Y_pos;

    SDL_Texture* image;
    SDL_Rect rect;
    SDL_Rect crop;

    int image_width;
    int image_height;

    float xscale;
    float yscale;

    int currentFrame;
    float animationTime;

    int frameWidth;
    int frameHeight;

    SDL_Renderer* renderer;
    SDL_Point* center;
    SDL_RendererFlip flip;
};