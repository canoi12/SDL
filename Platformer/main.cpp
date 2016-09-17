
#include "Utils.h"

std::vector<GameObject*> objects;
//std::vector<SDL_Rect> tileset;


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

    //tileset.push_back(teste);

    /*SDL_Texture* image = NULL;
    image = IMG_LoadTexture(renderer,"assets/bg_sky.png");
    if (image == NULL)
        std::cout << "Erro ao carregar a imagem" << std::endl;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 128;
    rect.h = 128;*/

    /*SDL_Texture* tileset_image = IMG_LoadTexture(renderer,"assets/ground.png");
    SDL_Rect teste;
    teste.x = 0;
    teste.y = 0;
    teste.w = 16;
    teste.h = 16;*/

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


    float timeCheck = SDL_GetTicks();
    float delta = 0;
    float time = SDL_GetTicks() / 1000.f;

    float deltaAcumulator = 0.f;
    int i = 0;

    float ntime = 0.f;
    float fps;

    ScreenManager::addScreen("menu", new GameScreen());

    /*for(int i = 0; i < 4; i++){
        objects.push_back(new Enemy("assets/box.png", i*16, 120));
        objects[i]->setQuad(0,0,16,16);
        //objects[i]->setX(i*16);
    }*/
    objects.push_back(new Enemy("assets/skeleton.png", 0, 0));
    objects.push_back(new Player("assets/astronaut.png", 300, 0));
    objects[1]->setQuad(0,0,16,16);

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

        for(int i = 0; i < 512; i+=16)
        {
            bg_rect.y = i-Camera::Y;
            for(int j = 0; j < 512; j += 16){
                bg_rect.x = j-Camera::X;
                SDL_RenderCopy(renderer,bg_image,&bg_src,&bg_rect);
            }
        }

        ScreenManager::Update(delta);
        ScreenManager::Draw();

        //std::cout << "Funcionando até aqui" << std::endl;
        /*for (int yy = 0; yy < height; yy++){
            for(int xx = 0; xx < width; xx++){
                teste.x = xx*16 - Camera::X;
                teste.y = yy*16 - Camera::Y;
                SDL_RenderCopy(renderer,tileset_image,&tileset[Utils::tilemap[xx][yy]-1],&teste);
            }
        }*/


        for(unsigned int i = 0; i < objects.size(); i++){
            //player->collision(enemies[i]);
            /*for(int j = 0; j < objects.size(); j++){
                if (objects[i] != objects[j])
                    objects[i]->collision(objects[j]);
            }*/
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
            fps = 1.f/delta;
            i = 0;
            deltaAcumulator = 0.f;
        }

        timeCheck = SDL_GetTicks();

        if (1000/FPS > SDL_GetTicks()-timeCheck)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-timeCheck));
    }

}