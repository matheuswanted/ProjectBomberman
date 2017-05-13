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
Tile * Map::GetCellFromMap(float x, float y){

    auto layers = map->GetLayers();
    tmx::MapLayer& layer = layers[1];
    sf::Vector2u mapsize = map->GetMapSize();
    float mapRows = mapsize.x / 32;
    int row, col;

    if(GetTileFromLayer(layer,mapRows,x,y,16,16,row,col))
        return new Tile(col,row);

    if(GetTileFromLayer(layer,mapRows,x,y,-16,16,row,col))
        return new Tile(col,row);

    if(GetTileFromLayer(layer,mapRows,x,y,16,-16,row,col))
        return new Tile(col,row);

    if(GetTileFromLayer(layer,mapRows,x,y,-16,-16,row,col))
        return new Tile(col,row);

    return NULL;
}



int Map::GetTileFromLayer(tmx::MapLayer& layer,float mapRows ,float x,float y,float deltaX,float deltaY, int &row, int &col){
    x += deltaX;
    y += deltaY;
    row = floor(y / 32);
    col = floor(x / 32);
    return layer.tiles[row*mapRows + col].gid;
}



