#include "MainCharacter.h"

float approach(float v1, float v2, float delta)
{
    if (v1 < v2)
        v1 += delta;
    else if (v1 > v2)
        v1 -= delta;

    if (v1 >= v2-0.05 && v1 <= v2+0.05)
        v1 = v2;

    return v1;
}

MainCharacter::MainCharacter(CSDL_Setup* passed_SDL_Setup)
{
    csdl_setup = passed_SDL_Setup;

    warrior = new CSprite(csdl_setup->getRenderer(),"assets/warrior2.png",0,50,16,16);
    warrior->setUpAnimation(16,16);
    warrior->setOrigin(warrior->getWidth()/2.f,warrior->getHeight()/2.f);

    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;

    dx = 0;
    dy = 0;

    friction = 0.8f;
    gravity = 0.2f;

    xscale = 1.f;
    yscale = 1.f;
}

MainCharacter::~MainCharacter(void)
{
    delete warrior;
}

void MainCharacter::Draw()
{
    warrior->Draw();
}

void MainCharacter::Update(float delta)
{

    switch(csdl_setup->getMainEvent()->type)
        {
        case SDL_KEYDOWN:
            switch(csdl_setup->getMainEvent()->key.keysym.sym)
            {
            case SDLK_LEFT:
                moveLeft = true;
                dx = -(50*delta);
                break;
            case SDLK_RIGHT:
                moveRight = true;
                dx = (50*delta);
                break;
            case SDLK_UP:
                if (!moveUp){
                    dy = -3.0f;
                    xscale = 0.6f;
                    yscale = 1.4f;
                }
                moveUp = true;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch(csdl_setup->getMainEvent()->key.keysym.sym)
            {
            case SDLK_LEFT:
                moveLeft = false;
                break;
            case SDLK_RIGHT:
                moveRight = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }


        if (!moveLeft && !moveRight){
            dx *= friction;
            warrior->playAnimation(0,2,0,0.6);
        }
        else {
            warrior->playAnimation(0,5,1,0.6);
        }

        /*if (moveLeft) {
            warrior->setX(warrior->getX()-(50*delta));
        }
        if (moveRight){
            warrior->setX(warrior->getX()+(50*delta));
        }*/

        //std::cout << dx << std::endl;

        warrior->setX(warrior->getX()+dx);
        warrior->setY(warrior->getY()+dy);

        if (warrior->getY() < 120){
            dy += gravity;
        } else {
            dy = 0;
            moveUp = false;
        }

}