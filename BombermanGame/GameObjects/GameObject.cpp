#include "GameObject.h"
#include <cmath>

GameObject::GameObject(){
}
void GameObject::Draw(cgf::Game* game){
    game->getScreen()->draw(sprite);
}

void GameObject::HandleCollision(GameObject * source){
}

void GameObject::HandleCollision(Tile* source){
}
void GameObject::Update(cgf::Game * game){
    Step(game->getUpdateInterval());
}

bool GameObject::IsDead(){
    return lifePoints == 0;
}
void GameObject::SetTile(){
    step->height = 32;
    step->width = 32;
    step->x = sprite.getPosition().x;
    step->y = sprite.getPosition().y;
    step->speedX = sprite.getXspeed();
    step->speedY = sprite.getYspeed();
    step->offset = 0;
    step->updateAnimOnly = false;
}
void GameObject::Step(double interval){
    float x = sprite.getPosition().x,
          y = sprite.getPosition().y;
    step->x = x + (step->speedX/1000 * interval);
    step->y = y + (step->speedY/1000 * interval);
    step->updateAnimOnly = false;
}
Tile* GameObject::GetTile(){
    return step;
}
ObjectType GameObject::GetType(){
    return type;
}
void GameObject::AdjustPosition(Tile * tile){
    float newValue;
    float horizontalCollisionGrade = fabs(step->x - tile->x);
    float verticalCollisionGrade = fabs((step->y + step->offset) - (tile->y + tile->offset));

    bool isHorizontalCollision = horizontalCollisionGrade > 25 && (horizontalCollisionGrade > verticalCollisionGrade || horizontalCollisionGrade == verticalCollisionGrade);
    bool isVerticalCollision = verticalCollisionGrade > 25 && (horizontalCollisionGrade < verticalCollisionGrade || horizontalCollisionGrade == verticalCollisionGrade);

    if(isHorizontalCollision){
        if(tile->x > step->x)
            newValue = tile->x - (tile->width/2) - (step->width/2) ;
        else if(tile->x < step->x)
            newValue = tile->x + (tile->width/2) + (step->width/2) ;
        else
            newValue = 0;
        if(newValue){
            step->x = newValue;
            step->updateAnimOnly = true;
        }
    }

    if(isVerticalCollision){
        if((tile->y + tile->offset) > (step->y + step->offset))
            newValue = tile->y - (step->height) - step->offset - tile->offset;
        else if((tile->y + tile->offset) < (step->y + step->offset))
            newValue = tile->y + (tile->height) - step->offset - tile->offset;
        else
            newValue = 0;
        if(newValue){
            step->y = newValue;
            step->updateAnimOnly = true;
        }
    }
}

void GameObject::Destroy(){

}
