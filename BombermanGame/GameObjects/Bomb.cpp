#include<iostream>
#include "Bomb.h"
#include "Player.h"
#include "GamePlayState.h"

using namespace std;

Bomb::Bomb(int x, int y){
    sprite.load("data/Sprites/Bombs/bomb.png", 32, 32, 5, 5, 5, 5, 6, 1, 6);
    sprite.loadAnimation("data/Sprites/Bombs/bomb_anim.xml");
    sprite.setPosition(x, y);
    sprite.setAnimation("explode");
    sprite.setAnimRate(4);
    sprite.play();
    music.openFromFile("data/Effects/bomb_put.wav");
    music.setVolume(50);  // 30% do volume máximo
    music.play();

    type = ObjectType::Bomb;
    SetTile();
    radius = 1;
}

Bomb::Bomb(int x, int y,int radius, GameObject * player, cgf::GameState * explosionHandler) : Bomb(x,y)
{
    this->explosionHandler = explosionHandler;
    this->player = player;
    this->radius = radius;
}

void Bomb::Update(cgf::Game* game) {
    sprite.update(game->getUpdateInterval());
    if(sprite.isStopped()){
        lifePoints = 0;
        if(player != NULL)
            ((Player*)player)->GetBomb();
        if(explosionHandler != NULL)
            Explode();
    }
    GameObject::Update(game);
}

void Bomb::Explode(){
    GamePlayState* handler = ((GamePlayState*)explosionHandler);
    int j = 0;
    float x = step->x, y = step->y;
    bool isEnd = true;
    handler->InsertObjectInGame(new Explosion(x,y,0,false),true);

    for(j = 1;j <= radius;j++){
        y = step->y + j*32;
        if(!handler->InsertObjectInGame(new Explosion(x,y,1,j == radius),false))
            break;
    }
    y = step->y;
    for(j = 1;j <= radius;j++){
        y = step->y - j*32;
        if(!handler->InsertObjectInGame(new Explosion(x,y,2,j == radius),false))
            break;
    }
    y = step->y;
    isEnd = true;
    for(j = 1;j <= radius;j++){
        x = step->x - j*32;
        if(!handler->InsertObjectInGame(new Explosion(x,y,3,j == radius),false))
            break;
    }
    x = step->x;
    isEnd = true;
    for(j = 1;j <= radius;j++){
        x = step->x + j*32;
        if(!handler->InsertObjectInGame(new Explosion(x,y,4,j == radius),false))
            break;
    }
    music.openFromFile("data/Effects/bomb_explosion.wav");
    music.setVolume(30);  // 30% do volume máximo
    music.play();
}


void Bomb::HandleCollision(GameObject* source){

}

