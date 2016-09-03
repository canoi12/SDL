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
#include <tinyxml.h>

TiXmlDocument doc("assets/levelteste.tmx");

std::vector<GameObject*> objects;

const int FPS = 60;

int main(int argc, char **argv)
{
    doc.LoadFile();

    TiXmlElement* root = doc.FirstChildElement();
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
    elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();

        std::cout << elemName << std::endl;
    }
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

    SDL_Texture* bg_image = IMG_LoadTexture(renderer,"assets/bg.png");
    SDL_Rect bg_rect;
    SDL_Rect bg_src;
    bg_rect.x = 0;
    bg_rect.y = 0;
    bg_rect.w = 16;
    bg_rect.h = 16;

    bg_src.x = 0;
    bg_src.y = 0;
    bg_src.w = 16;
    bg_src.h = 16;

   /* Player* player = new Player("assets/astronaut.png");
    player->setQuad(0,0,16,16);*/

    objects.push_back(new Player("assets/astronaut.png", 0, 0));
    objects[0]->setQuad(0,0,16,16);

    float timeCheck = SDL_GetTicks();
    float delta = 0;
    float time = SDL_GetTicks() / 1000.f;

    float deltaAcumulator = 0.f;
    int i = 0;

    float ntime = 0.f;
    float fps = 0;

    for(int i = 1; i < 5; i++){
        objects.push_back(new Enemy("assets/box.png", i*16, 120));
        objects[i]->setQuad(0,0,16,16);
        //objects[i]->setX(i*16);
    }

    /*enemies.push_back(new Enemy("assets/box.png"));
    enemies[4]->setQuad(0,0,16,16);
    enemies[4]->setX(400);*/

    //std::cout << enemies.size() << std::endl;


    while(Event::getEvent()->type != SDL_QUIT)
    {
        SDL_PollEvent(Event::getEvent());

        SDL_SetRenderDrawColor(Renderer::getRenderer(),0,0,0,255);
        SDL_RenderClear(renderer);

        //SDL_RenderCopy(renderer,image,NULL,&rect);
        /*bg_rect.x = -Camera::X;
        SDL_RenderCopy(renderer,bg_image,&bg_src,&bg_rect);
        bg_rect.x = 128-Camera::X;
        SDL_RenderCopy(renderer,bg_image,&bg_src,&bg_rect);
        bg_rect.x = 256-Camera::X;
        SDL_RenderCopy(renderer,bg_image,&bg_src,&bg_rect);
        bg_rect.x = 384-Camera::X;
        SDL_RenderCopy(renderer,bg_image,&bg_src,&bg_rect);
        */
        for(int i = 0; i < 128; i+=16)
        {
            bg_rect.y = i-Camera::Y;
            for(int j = 0; j < 512; j += 16){
                bg_rect.x = j-Camera::X;
                SDL_RenderCopy(renderer,bg_image,&bg_src,&bg_rect);
            }
        }


        for(int i = 0; i < objects.size(); i++){
            //player->collision(enemies[i]);
            for(int j = 0; j < objects.size(); j++){
                if (objects[i] != objects[j])
                    objects[i]->collision(objects[j]);
            }
            objects[i]->Update(delta);
            objects[i]->Draw();
        }

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