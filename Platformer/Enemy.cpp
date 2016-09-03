#include "Enemy.h"

Enemy::Enemy(std::string img_path, float x, float y)
{
    int image_width, image_height;
    image = IMG_LoadTexture(Renderer::getRenderer(),img_path.c_str());
    rect.x = 0;
    rect.y = 0;
    SDL_QueryTexture(image, NULL, NULL, &image_width, &image_height);
    rect.w = image_width;
    rect.h = image_height;

    origin = {image_width/2, image_height/2};
    flip = SDL_FLIP_NONE;
    crop = rect;
    setX(x);
    setY(y);

    dx = 0.f;
    dy = 0.f;

    xscale = 1.f;
    yscale = 1.f;

    width = image_width;
    height = image_height;

    bounce = 0.0f;
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Update(float delta)
{

    if (y < 128-origin.y){
        dy += 0.2f;
    }
    else {
        dy *= -bounce;
        if(dy >= -0.5f && dy <= 0.5f)
        {
            dy = 0;
        }
    }

    //std::cout << dy << std::endl;

    x += dx;
    y += dy;

    x = fmax(origin.x-4,fmin(x,512+4-origin.x));
    y = fmax(origin.y,fmin(y,128-origin.y));

    rect.x = (int)(x - (origin.x*xscale) - Camera::X);
    rect.y = (int)(y - (origin.y*yscale) - Camera::Y);

    rect.w = width  * xscale;
    rect.h = height * yscale;
}

void Enemy::Draw()
{
    SDL_RenderCopyEx(Renderer::getRenderer(),image,&crop,&rect,0,&origin,flip);
}