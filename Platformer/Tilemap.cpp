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

        if(elemName == "tileset")
        {
            for (TiXmlElement* tile = elem->FirstChildElement(); tile != NULL;
                tile = tile->NextSiblingElement())
                {
                    std::string nameteste = tile->Value();

                    if (nameteste == "tile")
                    {
                        int id = Utils::CharToInt(tile->Attribute("id"));
                        TiXmlElement* propertie = tile->FirstChildElement();
                        for(TiXmlElement* prop = propertie->FirstChildElement(); prop != NULL;
                            prop = prop->NextSiblingElement())
                            {
                                //screens.insert(std::pair<std::string, GameScreen*>(name, screen));
                                std::string propname = prop->Attribute("name");
                                //std::cout << propname << " " << id << std::endl;
                                //properties.insert(std::pair<std::string, int>(propname, id));
                                properties[propname][id] = Utils::CharToInt(prop->Attribute("value"));

                                //std::cout << properties["solid"].size() << std::endl;
                            }
                    }
                }
        }

        if(elemName == "layer")
        {

            int **tiletest = new int *[width];
            //std::cout << "Funcionando até aqui" << std::endl;
            for (int i = 0; i < width; i++)
            {
                tiletest[i] = new int[height];
            }

            tilemap.push_back(tiletest);
            int x_teste = 0;
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

    //std::cout << "teste" << std::endl;
    //std::cout << properties["solid"][0] << std::endl;
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
                //std::cout << rect.x << " " << Camera::X << std::endl;
                if (rect.x + Camera::X > Camera::X - 96 &&
                    rect.x + Camera::X < Camera::X + 192 &&
                    rect.y + Camera::Y > Camera::Y - 96 &&
                    rect.y + Camera::Y < Camera::Y + 192)
                    SDL_RenderCopy(Renderer::getRenderer(),image,&tiles[tilemap[l][xx][yy]-1],&rect);
            }
        }
    }
    std::cout << Camera::X << std::endl;
}