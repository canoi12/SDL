#include "Block.h"

Block::Block(){}

Block::Block(std::string img_path, float x, float y) {
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
}

Block::~Block(){}

void Block::Update(float delta) {

}

void Block::Draw() {

}