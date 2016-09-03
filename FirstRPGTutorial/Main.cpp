#include "Main.h"

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{

    ScreenWidth = passed_ScreenWidth;
    ScreenHeight = passed_ScreenHeight;
    quit = false;

    csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);
    sky = new CSprite(csdl_setup->getRenderer(), "assets/bg_sky.png",0,0,128,128);
    sky->setUpAnimation(128,128);

    moveRight = false;
    moveLeft = false;
    moveUp = false;
    moveDown = false;

    timeCheck = SDL_GetTicks();

    player = new MainCharacter(csdl_setup);


}

CMain::~CMain(void)
{
}

void CMain::GameLoop(void)
{
    timeCheck = 0;
    float delta = 0.0f;
    float time = SDL_GetTicks() / 1000.f;
    float deltaAcumulator = 0.f;
    int i = 0;
    float ntime = 0.0f;
    float fps = 0;

    //long now = SDL_GetTic
    while(!quit && csdl_setup->getMainEvent()->type != SDL_QUIT)
    {
        moveLeft = false;
        moveRight = false;

        ntime = SDL_GetTicks() / 1000.f;
        delta = ntime - time;

        time = ntime;

        deltaAcumulator += delta;

        i++;

        if (i == 10) {
            float avgDelta = deltaAcumulator/10.f;
            fps = 1.f/delta;
            i = 0;
            deltaAcumulator = 0.f;
        }

        timeCheck = SDL_GetTicks();
        csdl_setup->Begin();
        //SDL_RenderCopy(csdl_setup->getRenderer(),sky_image,NULL,&sky_rect);
        sky->Draw();
        player->Update(delta);
        player->Draw();
        /*warrior->Draw();
        warrior->playAnimation(0,5,1,0.6);*/

        /*switch(csdl_setup->getMainEvent()->type)
        {
        case SDL_KEYDOWN:
            switch(csdl_setup->getMainEvent()->key.keysym.sym)
            {
            case SDLK_LEFT:
                moveLeft = true;
                break;
            case SDLK_RIGHT:
                moveRight = true;
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
        }*/

        if(1000/FPS > SDL_GetTicks()-timeCheck)
            //delta = ((float)(SDL_GetTicks()-timeCheck)) / 1000;
            SDL_Delay(1000/FPS-(SDL_GetTicks()-timeCheck));
        //if (timeCheck + 5 < SDL_GetTicks()){
            //SDL_GetTicks();
            /*if (moveLeft) {
                warrior->setX(warrior->getX()-(100*delta));
            }
            if (moveRight){
                warrior->setX(warrior->getX()+(100*delta));
            }*/

            //std::cout << fps << std::endl;

            //timeCheck = SDL_GetTicks();
        //}

        csdl_setup->End();
    }
}