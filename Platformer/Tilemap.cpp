#include "Tilemap.h"

Tilemap::Tilemap() {}

Tilemap::Tilemap(std::string map_path) {
    TiXmlDocument doc(map_path);

    doc.LoadFile();

    TiXmlElement* root = doc.FirstChildElement();

    width = Utils::CharToInt(root->Attribute("width"));
    height = Utils::CharToInt(root->Attribute("height"));
    tile_size = Utils::CharToInt(root->Attribute("tilewidth"));

    image = IMG_LoadTexture(Renderer::getRenderer(),"assets/ground2.png");
    rect.x = 0;
    rect.y = 0;
    rect.w = tile_size;
    rect.h = tile_size;

    map_width = width * tile_size;
    map_height = height * tile_size;

    SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);

    loadTiles();

    layers = 0;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
    elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();

        //std::cout << elemName << std::endl;

        if(elemName == "layer")
        {

            int **tiletest = new int *[width];
            std::cout << "Funcionando até aqui" << std::endl;
            for (int i = 0; i < width; i++)
            {
                tiletest[i] = new int[height];
            }

            tilemap.push_back(tiletest);
            int x_teste = 0;
            int y_teste = 0;
            int yy = 0;
            int xx = 0;
            TiXmlElement* data = elem->FirstChildElement();
            for(TiXmlElement* dat = data->FirstChildElement(); dat != NULL;
                dat = dat->NextSiblingElement()){
                //std::cout << "dat" << std::endl;
                xx = x_teste%width;
                //std::cout << x_teste%width << std::endl;
                if(xx % width == 0 and x_teste > 1)
                {
                    yy++;
                }
                //std::cout << xx << " " << yy << std::endl;
                //
                tilemap[layers][xx][yy] = Utils::CharToInt(dat->Attribute("gid"));
                //std::cout << "Funcionando até aqui " << xx << " " << yy << " : " << tilemap[layers][xx][yy] << std::endl;
                x_teste ++;
            }
            layers++;
        }
    }
}

Tilemap::~Tilemap() {}

void Tilemap::loadTiles() {
    for(int yy = 0; yy < img_height; yy += tile_size)
    {
        for(int xx = 0; xx < img_width; xx += tile_size)
        {
            SDL_Rect test;
            test.x = xx;
            test.y = yy;
            test.w = tile_size;
            test.h = tile_size;

            tiles.push_back(test);
        }
    }
}

void Tilemap::Update(float delta) {

}

void Tilemap::Draw() {
    for(int l = 0; l < layers; l++) {
        for (int yy = 0; yy < height; yy++){
            for(int xx = 0; xx < width; xx++){
                rect.x = xx*tile_size - Camera::X;
                rect.y = yy*tile_size - Camera::Y;
                SDL_RenderCopy(Renderer::getRenderer(),image,&tiles[tilemap[l][xx][yy]-1],&rect);
            }
        }
    }
}