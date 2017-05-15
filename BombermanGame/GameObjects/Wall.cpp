#include "Wall.h"
Wall::Wall(int x, int y){
    sprite.load("data/Sprites/Tiles/tile_brick.png");
    sprite.setPosition(x, y);
    type = ObjectType::Wall;
    SetTile();

}
void Wall::Update(cgf::Game* game){
    if(lifePoints == -1 )
        lifePoints = 0;
    GameObject::Update(game);
}
void Wall::HandleCollision(GameObject* source){


}
void Wall::Destroy(){
    lifePoints = 0;
    //sprite.setAnimRate(8);
}
