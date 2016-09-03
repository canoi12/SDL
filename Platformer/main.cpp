#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Event.h"
#include "Player.h"
#include "Keyboard.h"
#include "Enemy.h"
#include "Camera.h"
#include <iostream>
#include <vector>

std::vector<Enemy*> enemies (4);

const int FPS = 60;

int main(int argc, char **argv)
{
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Hello World",50,50,512,512,SDL_WINDOW_SHOWN);

    /*SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);*/
    Renderer* render = Renderer::getInstance();
    render->setWindow(window);  
    SDL_Renderer* renderer = render->getRenderer();

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(renderer, 128,128);
    Keyboard::getKeyboard();


    SDL_Event* mainEvent = new SDL_Event();

    /*SDL_Texture* image = NULL;
    image = IMG_LoadTexture(renderer,"assets/bg_sky.png");
    if (image == NULL)
        std::cout << "Erro ao carregar a imagem" << std::endl;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 128;
    rect.h = 128;*/
    Player* player = new Player("assets/astronaut.png");
    player->setQuad(0,0,16,16);

    float timeCheck = SDL_GetTicks();
    float delta = 0;
    float time = SDL_GetTicks() / 1000.f;

    float deltaAcumulator = 0.f;
    int i = 0;

    float ntime = 0.f;
    float fps = 0;

    for(int i = 0; i < enemies.size(); i++){
        enemies[i] = new Enemy("assets/warrior2.png");
        enemies[i]->setQuad(0,0,16,16);
    }
    enemies[0]->setX(0);
    enemies[1]->setX(100);
    enemies[2]->setX(200);
    enemies[3]->setX(300);

    //std::cout << enemies.size() << std::endl;


    while(Event::getEvent()->type != SDL_QUIT)
    {
        SDL_PollEvent(Event::getEvent());

        SDL_SetRenderDrawColor(Renderer::getRenderer(),0,0,0,255);
        SDL_RenderClear(renderer);

        //SDL_RenderCopy(renderer,image,NULL,&rect);

        for(int i = 0; i < enemies.size(); i++){
            player->collision(enemies[i]);
            enemies[i]->Update(delta);
            enemies[i]->Draw();
        }
        player->Update(delta);
        player->Draw();

        SDL_RenderPresent(renderer);

        ntime = SDL_GetTicks() / 1000.f;
        delta = ntime - time;

        time = ntime;

        deltaAcumulator += delta;

        i++;

        if(i == 10) {
            float avgDelta = deltaAcumulator/10.f;
            fps = 1.f/delta;
            i = 0;
            deltaAcumulator = 0.f;
        }

        timeCheck = SDL_GetTicks();

        if (1000/FPS > SDL_GetTicks()-timeCheck)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-timeCheck));
    }

}