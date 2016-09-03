#include "Main.h";


int main (int argc, char *argv[])
{

    /*bool quit = false;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = NULL;

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event* mainEvent = new SDL_Event();

    SDL_Texture* grass_image = NULL;
    grass_image = IMG_LoadTexture(renderer, "assets/bg_sky.png");

    SDL_Rect grass_rect;
    grass_rect.x = 10;
    grass_rect.y = 50;
    grass_rect.w = 256;
    grass_rect.h = 256;

    SDL_Texture* warrior_image = NULL;
    warrior_image = IMG_LoadTexture(renderer,"assets/warrior-idle.png");

    SDL_Rect warrior_rect;
    warrior_rect.x = 200;
    warrior_rect.y = 100;
    warrior_rect.w = 96;
    warrior_rect.h = 32;

    while(!quit && mainEvent->type != SDL_QUIT)
    {
        SDL_PollEvent(mainEvent);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,grass_image,NULL,&grass_rect);
        SDL_RenderCopy(renderer, warrior_image, NULL, &warrior_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(sky_image);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete mainEvent;

    SDL_Quit();*/

    CMain* cmain = new CMain(512,512);

    cmain->GameLoop();

    //delete cmain;

    return 0;
}