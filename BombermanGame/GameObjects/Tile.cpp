#include "Tile.h"
Tile::Tile(int col,int row){
    x =(col*32);
    y =(row*32);
    width = 29;
    height = 29;
    speedX = 0;
    speedY = 0;
    this->updateAnimOnly = false;
    this->offset = 0;
}
Tile::Tile(float x,float y,float w,float h){
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    speedX = 0;
    speedY = 0;
    this->updateAnimOnly = false;
    this->offset = 0;
}
