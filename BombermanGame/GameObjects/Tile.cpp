#include "Tile.h"
Tile::Tile(int col,int row){
    x =(col*32)+32/2;
    y =(row*32)+32/2;
    width = 32;
    height = 32;
}
Tile::Tile(float x,float y,float w,float h){
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}
