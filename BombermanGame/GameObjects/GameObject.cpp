#include "GameObject.h"
#include <cmath>

GameObject::GameObject(){

}

void GameObject::DecreaseLife(int damage){

}
void GameObject::Draw(cgf::Game* game){

}
void GameObject::HandleCollision(GameObject * source){
}

void GameObject::HandleCollision(Tile* source){
}
void GameObject::Move(int direction){}

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
    float horizontalCollisionGrade = step->x - tile->x;
    float verticalCollisionGrade = (step->y + step->offset) - (tile->y + tile->offset);

    if(tile->x > step->x)
        horizontalCollisionGrade = tile->x - step->x;
    if((tile->y + tile->offset) > (step->y + step->offset))
        verticalCollisionGrade = (tile->y + tile->offset) - (step->y + step->offset);
    bool xMove = step->speedX != 0, yMove = step->speedY != 0;
    bool isHorizontalCollision = horizontalCollisionGrade > verticalCollisionGrade || horizontalCollisionGrade == verticalCollisionGrade;
    bool isVerticalCollision = horizontalCollisionGrade < verticalCollisionGrade || horizontalCollisionGrade == verticalCollisionGrade;

    if(isHorizontalCollision){
        if(xMove && tile->x > step->x)
            newValue = tile->x - (tile->width/2) - (step->width/2) ;
        else if(xMove && tile->x < step->x)
            newValue = tile->x + (tile->width/2) + (step->width/2) ;
        else
            newValue = 0;
        if(newValue){
            step->x = newValue;
            step->updateAnimOnly = true;
        }
    }

    if(isVerticalCollision){
        if(yMove && (tile->y + tile->offset) > (step->y + step->offset))
            newValue = tile->y - (tile->height/2) - (step->height/2) - step->offset - tile->offset;
        else if(yMove && tile->y < step->y)
            newValue = tile->y + (tile->height/2) + (step->height/2) - step->offset - tile->offset;
        else
            newValue = 0;
        if(newValue){
            step->y = newValue;
            step->updateAnimOnly = true;
        }
    }
}
