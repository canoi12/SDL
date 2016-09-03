#include "GameObject.h"

GameObject::GameObject(std::string img_path)
{
    /*int image_width, image_height;
    image = IMG_LoadTexture(Renderer::getRenderer(),img_path.c_str());
    rect.x = 0;
    rect.y = 0;
    SDL_QueryTexture(image, NULL, NULL, &image_width, &image_height);
    rect.w = image_width;
    rect.h = image_height;

    origin = {image_width/2, image_height/2};
    flip = SDL_FLIP_NONE;
    crop = rect;
    x = 0.f;
    y = 0.f;

    dx = 0.f;
    dy = 0.f;

    xscale = 1.f;
    yscale = 1.f;

    oxscale = 1.f;

    bounce = 0.0f;*/
}

GameObject::GameObject(){}

GameObject::~GameObject(){}

void GameObject::playAnimation(int beginFrame, int endFrame, int row, float speed)
{
    if (currentTime < speed)
        currentTime += 0.1f;
    else{
        currentFrame++;
        currentTime = 0.f;
    }
    if (currentFrame > endFrame)
        currentFrame = beginFrame;

    crop.x = currentFrame * crop.w;
    crop.y = row*crop.h;
}

void GameObject::setQuad(int x, int y, int w, int h)
{


    crop.x = x;
    crop.y = y;
    crop.w = w;
    crop.h = h;

    rect.w = w;
    rect.h = h;
    width = w;
    height = h;

    origin = {w/2,h/2};
    //origin = {0,0};
}

void GameObject::setX(float X)
{
    x = X;
    rect.x = (int)(x - (origin.x) - Camera::X);
}

void GameObject::setY(float Y)
{
    y = Y;
    rect.y = (int)(y-(origin.y) - Camera::Y);
}

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}

int GameObject::getCenterX()
{
    return (int)(x-(width/2));
}

int GameObject::getCenterY()
{
    return (int)(y-(height/2));
}

int GameObject::getWidth()
{
    return width;
}

int GameObject::getHeight()
{
    return height;
}

bool GameObject::collision(GameObject* obj2){}

void GameObject::Update(float delta)
{
    /*if (Event::getEvent()->type == SDL_KEYDOWN)
    {
        if(Event::getEvent()->key.keysym.sym == SDLK_LEFT)
        {
            flip = SDL_FLIP_NONE;
            dx = -delta*50;
        }
        if(Event::getEvent()->key.keysym.sym == SDLK_RIGHT)
        {
            flip = SDL_FLIP_HORIZONTAL;
            dx = delta*50;
        }
    }*/

    /*if (keyDown("right")){
        dx = delta*100;
        flip = SDL_FLIP_NONE;
    }
    else if (keyDown("left")){
        dx = -delta*100;
        flip = SDL_FLIP_HORIZONTAL;
    }
    
    if (!keyDown("right") && !keyDown("left")){
        dx = 0;
        playAnimation(0,2,0,0.6f);
    } else if(keyDown("right") || keyDown("left")) {
        playAnimation(0,5,1,0.6f);
    }

    if (y < 128-origin.y){
        dy += 0.2f;
    }
    else {
        dy *= -bounce;
        if(!isGround)
        {
            isGround = true;
            xscale = 1.5f;
            yscale = 0.5f;
        }
        if(dy >= -0.5f && dy <= 0.5f)
        {
            dy = 0;
        }
        if (keyDown("up")){
            dy = -3.2f;
            xscale = 0.5f;
            yscale = 1.5f;
            isGround = false;
        }
    }

    //std::cout << dy << std::endl;

    x += dx;
    y += dy;

    x = fmax(origin.x-4,fmin(x,128+4-origin.x));
    y = fmax(origin.y,fmin(y,128-origin.y));

    rect.x = (int)(x - (origin.x*xscale));
    rect.y = (int)(y-(origin.y*yscale));

    xscale = approach(xscale, 1, 0.05);
    yscale = approach(yscale, 1, 0.05);

    //oxscale = approach(xscale)

    rect.w = (width) * xscale;
    rect.h = height * yscale;*/


}

void GameObject::Draw()
{
    //SDL_RenderCopyEx(Renderer::getRenderer(),image,&crop,&rect,0,&origin,flip);
}