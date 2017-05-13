#ifndef TILE_H
#define TILE_H
typedef struct Tile{
    public:
    Tile(){}
    Tile(float x,float y,float w,float h);
    Tile(int col,int row);
    float x, y, width, height;
} Tile;
#endif
