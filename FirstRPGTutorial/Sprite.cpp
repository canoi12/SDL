#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer, std::string path, int x, int y, int w, int h)
{
    renderer = passed_renderer;

    image = NULL;
    image = IMG_LoadTexture(renderer,path.c_str());

    if (image == NULL)
    {
        std::cout << "Couldn't Load Image!" << std::endl;
    }

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image, NULL, NULL, &image_width, &image_height);

    crop.x = 0;
    crop.y = 0;
    crop.w = image_width/7;
    crop.h = image_height / 2;

    X_pos = x;
    Y_pos = y;

    Origin_X = 0.f;
    Origin_Y = 0.f;

    currentFrame = 0;
    animationTime = 0.f;

    frameWidth = 16;
    frameHeight = 16;

    xscale = 1.f;
    yscale = 1.f;

    //center = new SDL_Point(0.f, 0.f);
    flip = SDL_FLIP_NONE;
}

void CSprite::playAnimation(int beginFrame, int endFrame, int row, float speed)
{
    if (animationTime < speed)
    {
        animationTime += 0.1f;
    } else {

        currentFrame++;
        animationTime = 0.f;
    }
    if (endFrame < currentFrame)
        currentFrame = beginFrame;
    int numCols = (image_width/frameWidth);
    int numRows = (image_height/frameHeight);
    crop.x = currentFrame*(image_width/numCols);
    crop.y = row * (image_height/numRows);

    crop.w = image_width/numCols;
    crop.h = image_height/numRows;
}

void CSprite::setUpAnimation(int passed_frameWidth, int passed_frameHeight)
{
    frameWidth = passed_frameWidth;
    frameHeight = passed_frameHeight;

    int numCols = (image_width/frameWidth);
    int numRows = (image_height/frameHeight);

    crop.w = image_width/numCols;
    crop.h = image_height/numRows;
}

CSprite::~CSprite(void)
{
    SDL_DestroyTexture(image);
}

void CSprite::Draw()
{
    SDL_RenderCopy(renderer,image,&crop,&rect);
}

void CSprite::setX(float X)
{
    X_pos = X;
    rect.x = int(X_pos - Origin_X);
}
void CSprite::setY(float Y)
{
    Y_pos = Y;
    rect.y = int(Y_pos - Origin_Y);
}

int CSprite::getFrameWidth()
{
    return frameWidth;
}

int CSprite::getFrameHeight()
{
    return frameHeight;
}

void CSprite::setPosition(float X, float Y){
    X_pos = X;
    Y_pos = Y;
    rect.x = int(X_pos - Origin_X);
    rect.y = int(Y_pos - Origin_Y);
}

float CSprite::getX()
{
    return X_pos;
}

float CSprite::getY()
{
    return Y_pos;
}

int CSprite::getWidth()
{
    return rect.w;
}

int CSprite::getHeight()
{
    return rect.h;
}

int CSprite::setWidth(int W)
{
    rect.w = W;
}

int CSprite::setHeight(int H)
{
    rect.h = H;
}

void CSprite::setOrigin(float X, float Y)
{
    Origin_X = X;
    Origin_Y = Y;

    setPosition(getX(), getY());
}