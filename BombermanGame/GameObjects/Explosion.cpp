#include "Explosion.h"
Explosion::Explosion(float x, float y, int side, bool isEnd){
    sprite.load("data/Sprites/Explosion/explosion_sheet.png",32,32,5,5,5,5,5,9);
    sprite.loadAnimation("data/Sprites/Explosion/explosion_anim.xml");
    sprite.setPosition(x,y);
    switch(side){
        case 0:
            sprite.setAnimation("middle");
            break;
        case 1:
            if(isEnd)
                sprite.setAnimation("bot_max");
            else
                sprite.setAnimation("bot_min");
            break;
        case 2:
            if(isEnd)
                sprite.setAnimation("top_max");
            else
                sprite.setAnimation("top_min");
            break;
        case 3:
            if(isEnd)
                sprite.setAnimation("left_max");
            else
                sprite.setAnimation("left_min");
            break;
        case 4:
            if(isEnd)
                sprite.setAnimation("right_max");
            else
                sprite.setAnimation("right_min");
            break;
        default: break;
    }
    sprite.setAnimRate(14);
    sprite.play();
    type = ObjectType::Explosion;
    SetTile();
}
void Explosion::Update(cgf::Game* game){
    if(sprite.isStopped())
        lifePoints = 0;
    sprite.update(game->getUpdateInterval());
    GameObject::Update(game);
}
void Explosion::HandleCollision(GameObject* source){

}
void Explosion::HandleCollision(Tile* source){

}
