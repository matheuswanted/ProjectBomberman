#ifndef MAP_H
#define MAP_H
#include <string>
#include <tmx/MapLoader.h>
class Map
{
    public:
        Map(std::string mapFolder, std::string mapName);
        ~Map();
        void Draw(sf::RenderWindow * screen);
        void Cleanup();
    private:
        tmx::MapLoader* map;
};
#endif // MAP_H
