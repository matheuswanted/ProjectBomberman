#ifndef MAP_H
#define MAP_H
#include <string>
#include <tmx/MapLoader.h>
#include "Tile.h"
class Map
{
    public:
        Map(std::string mapFolder, std::string mapName);
        ~Map();
        void Draw(sf::RenderWindow * screen);
        void Cleanup();
        Tile * GetCellFromMap(float x, float y);
    private:
        tmx::MapLoader* map;
        int GetTileFromLayer(tmx::MapLayer& layer, float mapRows,float x,float y,float deltaX,float deltaY, int &row, int &col);
};
#endif // MAP_H
