#include "Map.h"

Map::Map(std::string mapFolder, std::string mapName){
    map = new tmx::MapLoader(mapFolder);
    map->Load(mapName);
    music.openFromFile("data/Sounds/level-1.ogg");
    music.setVolume(30);  // 30% do volume máximo
    music.setLoop(true);  // modo de loop: repete continuamente.
    music.play();
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

bool Map::HasWallOnCell(float x,float y){
    auto layers = map->GetLayers();
    tmx::MapLayer& layer = layers[1];
    sf::Vector2u mapsize = map->GetMapSize();
    float mapRows = mapsize.x / 32;
    int row, col;
    return GetTileFromLayer(layer,mapRows,x,y,31,31,row,col);
}

Tile ** Map::GetPossibleCellCollisionsFromMap(float x, float y){

    auto layers = map->GetLayers();
    tmx::MapLayer& layer = layers[1];
    sf::Vector2u mapsize = map->GetMapSize();
    float mapRows = mapsize.x / 32;
    int row, col;
    Tile** tileArray = new Tile*[4];
    if(GetTileFromLayer(layer,mapRows,x,y,31,31,row,col))
        tileArray[0] = new Tile(col,row);
    else
        tileArray[0] = NULL;
    if(GetTileFromLayer(layer,mapRows,x,y,0,0,row,col))
        tileArray[1] = new Tile(col,row);
    else
        tileArray[1] = NULL;
    if(GetTileFromLayer(layer,mapRows,x,y,0,31,row,col))
        tileArray[2] = new Tile(col,row);
    else
        tileArray[2] = NULL;

    if(GetTileFromLayer(layer,mapRows,x,y,32,0,row,col))
        tileArray[3] = new Tile(col,row);
    else
        tileArray[3] = NULL;

    return tileArray;
}
int Map::GetRowCont(){
    return map->GetMapSize().x / 32;
}


int Map::GetTileFromLayer(tmx::MapLayer& layer,float mapRows ,float x,float y,float deltaX,float deltaY, int &row, int &col){
    x += deltaX;
    y += deltaY;
    row = floor(y / 32);
    col = floor(x / 32);
    return layer.tiles[row*mapRows + col].gid;
}



