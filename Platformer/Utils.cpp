#include "Utils.h"
#include "Tilemap.h"

bool Utils::check_ground(int x, int y, std::string type, int value, Tilemap* map)
{
    for (unsigned int i = 0; i< map->tilemap.size(); i++){
        int tested_tile = (map->tilemap[i][(x/map->tile_size)][y/map->tile_size]);
        if (map->properties[type][tested_tile-1] == value)
            return true;
    }
    return false;
}

bool Utils::check_ground(int x, int y, std::string type, int value)
{
    for (unsigned int i = 0; i< ScreenManager::currentScreen->map->tilemap.size(); i++){
        int tested_tile = (ScreenManager::currentScreen->map->tilemap[i][(x/ScreenManager::currentScreen->map->tile_size)][y/ScreenManager::currentScreen->map->tile_size]);
        if (ScreenManager::currentScreen->map->properties[type][tested_tile-1] == value)
            return true;
    }
    return false;
}