#include "MapEnemy.h"
#include "GamePlayState.h"
#include<iostream>
#include<cmath>
#include <stdlib.h>

using namespace std;

MapEnemy::MapEnemy(cgf::GameState * state, int x, int y){
    type = ObjectType::Enemy;
    walkStates[0] = "right";
    walkStates[1] = "left";
    walkStates[2] = "up";
    walkStates[3] = "down";

    currentDir = DOWN;

    sprite.load("data/Sprites/Player/secondary_white.png",32,51,5,5,5,5,4,4,16);
    sprite.loadAnimation("data/Sprites/Player/secondary.xml");
    sprite.setAnimation(walkStates[currentDir]);

    sprite.setPosition(x*32,(y*32)+18);
    sprite.setAnimRate(30);
    sprite.setScale(1,1);
    sprite.play();

    dirx = 0; // sprite dir: right (1), left (-1)
    diry = 1; // down (1), up (-1)
    SetTile();
    step->offset = 18;

    step->speedX = 50*dirx;
    step->speedY = 50*diry;
}

void MapEnemy::Update(cgf::Game* game){
    if (this->IsDying())
        return;

    if(step->updateAnimOnly){
        sprite.setPosition(step->x,step->y);
        sprite.update(game->getUpdateInterval(),false);
    }
    else{
        sprite.setXspeed(step->speedX);
        sprite.setYspeed(step->speedY);
        sprite.update(game->getUpdateInterval());
    }

    GameObject::Update(game);
}

void MapEnemy::HandleCollision(GameObject* source){
    HandleCollision(source->GetTile());
    if(source->GetType() == ObjectType::Explosion && !this->IsDying())
        this->Destroy();

}

void MapEnemy::Destroy(){
    GameObject::Destroy();
//    music.openFromFile("data/Effects/bomberman_dying.wav");
//    music.setVolume(30);  // 30% do volume máximo
//    music.play();
    sprite.setAnimation("death");

}

void MapEnemy::HandleCollision(Tile* tile){
    //AdjustPosition(tile);

    float newValue;
    float horizontalCollisionGrade = fabs(step->x - tile->x);
    float verticalCollisionGrade = fabs((step->y + step->offset) - (tile->y + tile->offset));

    bool isHorizontalCollision = horizontalCollisionGrade >= 25 && (horizontalCollisionGrade > verticalCollisionGrade || horizontalCollisionGrade == verticalCollisionGrade);
    bool isVerticalCollision = verticalCollisionGrade >= 25 && (horizontalCollisionGrade < verticalCollisionGrade || horizontalCollisionGrade == verticalCollisionGrade);

    if (isHorizontalCollision && dirx == 0)
        isHorizontalCollision = false;

    if (isVerticalCollision && diry == 0)
        isVerticalCollision = false;

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

    int newDir = currentDir;

    if (isVerticalCollision ) {

        if (diry == 1) {
            diry = -1;
            newDir = UP;
        } else {
            diry = 1;
            newDir = DOWN;
        }
    }

    if (isHorizontalCollision && ! isVerticalCollision ) {
        diry = 0;

        if (dirx == 1) {
            dirx = -1;
            newDir = LEFT;
        } else {
            diry = 1;
            newDir = RIGHT;
        }
    }


    if(currentDir != newDir) {
        sprite.setAnimation(walkStates[newDir]);
        currentDir = newDir;
        sprite.play();
        step->speedX = 50*dirx;
        step->speedY = 50*diry;
    }

}
