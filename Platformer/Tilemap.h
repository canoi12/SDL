#pragma once
#ifndef TILEMAP
#define TILEMAP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>
#include <sstream>
#include <tinyxml.h>

#include "Utils.h"
#include "Renderer.h"
#include "Camera.h"

class Tilemap {
public:
    Tilemap();
    Tilemap(std::string map_path);
    ~Tilemap();

    void loadMap(std::string map_path);

    void loadTiles();

    void Update(float delta);
    void Draw();

    std::vector<int**> tilemap;

    int width;
    int height;

    int map_width;
    int map_height;

    int tile_size;

private:
    SDL_Texture* image;
    SDL_Rect rect;

    std::vector<SDL_Rect> tiles;

    int img_width;
    int img_height;

    int layers;
};
#endif