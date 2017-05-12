#include "Map.h"

Map::Map(std::string mapFolder, std::string mapName){
    map = new tmx::MapLoader(mapFolder);
    map->Load(mapName);
}
Map::~Map(){
    this->Cleanup();
}

void Map::Cleanup(){
    delete map;
}

void Map::Draw(sf::RenderWindow * screen){
    map->Draw(*screen);
}
