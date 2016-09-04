#include "Utils.h"
#include "Tilemap.h"

bool Utils::check_solid(int x, int y, Tilemap* map)
{
    if (map->tilemap[0][(x/ScreenManager::currentScreen->map->tile_size)][y/ScreenManager::currentScreen->map->tile_size] != 0)
        return true;
    return false;
}