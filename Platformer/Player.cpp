#include "Player.h"

//bool isGround = false;

float approach(float v1, float v2, float dt)
{
    if (v1 < v2)
        v1 += dt;
    if (v1 > v2)
        v1 -= dt;

    if (v1 > v2-0.1 && v1 < v2+0.1){
        v1 = 1;
    }

    return v1;
}

Player::Player(std::string img_path)
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
    x = 0.f;
    y = 0.f;

    dx = 0.f;
    dy = 0.f;

    xscale = 1.f;
    yscale = 1.f;

    oxscale = 1.f;

    bounce = 0.0f;
    isGround = false;
}

Player::Player()
{

}

Player::~Player()
{

}

bool Player::collision(GameObject* obj2)
{
    float w = 0.5 * (width + obj2->getWidth());
    float h = 0.5 * (height + obj2->getHeight());

    float dx = getCenterX() - obj2->getCenterX();
    float dy = (getCenterY()) - obj2->getCenterY();

    if (abs(dx) <= w && abs(dy) <= h)
    {
        float wy = w * dy;
        float hx = h * dx;

        if (wy > hx){
            if (wy > -hx){
            }
            else{
                setX(obj2->getX()-(getWidth()));
            }
        } else {
            if (wy > -hx)
                setX(obj2->getX()+obj2->getWidth());
            else{
                setY(obj2->getY()-getHeight());
            }
                
        }
        return true;
    }
    return false;
}

void Player::Update(float delta)
{
    if (Keyboard::keyDown("right")){
        dx = delta*100;
        flip = SDL_FLIP_NONE;
    }
    else if (Keyboard::keyDown("left")){
        dx = -delta*100;
        flip = SDL_FLIP_HORIZONTAL;
    }
    
    if (!Keyboard::keyDown("right") && !Keyboard::keyDown("left")){
        dx = 0;
        playAnimation(0,3,0,0.6f);
    } else if(Keyboard::keyDown("right") || Keyboard::keyDown("left")) {
        playAnimation(0,4,1,0.6f);
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
        if (Keyboard::keyDown("up")){
            dy = -3.2f;
            xscale = 0.5f;
            yscale = 1.5f;
            isGround = false;
        }
    }

    //std::cout << dy << std::endl;

    x += dx;
    y += dy;

    x = fmax(origin.x-4,fmin(x,512+4-origin.x));
    y = fmax(origin.y,fmin(y,128-origin.y));

    rect.x = (int)(x - (origin.x*xscale) - Camera::X);
    rect.y = (int)(y - (origin.y*yscale) - Camera::Y);

    xscale = approach(xscale, 1, 0.05);
    yscale = approach(yscale, 1, 0.05);

    Camera::X = x - (origin.x) - 64;
    Camera::Y = y - (origin.y) - 64;

    //oxscale = approach(xscale)

    Camera::X = fmax(0,fmin(Camera::X, 512-128));
    Camera::Y = fmax(0,fmin(Camera::Y,128-128));

    rect.w = (width) * xscale;
    rect.h = height * yscale;
}

void Player::Draw()
{
    SDL_RenderCopyEx(Renderer::getRenderer(),image,&crop,&rect,0,&origin,flip);
}