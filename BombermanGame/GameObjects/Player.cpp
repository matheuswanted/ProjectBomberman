#include "Player.h"
#include "Bomb.h"
#include "GamePlayState.h"
#include<iostream>
#include<cmath>

using namespace std;

Player::Player(cgf::GameState * putBombHandler){
    type = ObjectType::Player;
    walkStates[0] = "right";
    walkStates[1] = "left";
    walkStates[2] = "up";
    walkStates[3] = "down";
    walkStates[4] = "right-stop";
    walkStates[5] = "left-stop";
    walkStates[6] = "up-stop";
    walkStates[7] = "down-stop";

    currentDir = DOWN;

    //sprite.load("data/Sprites/Player/player.png",32,49,0,0,0,0,1,12,12);
    //sprite.loadAnimation("data/Sprites/Player/playeranim.xml");
    sprite.load("data/Sprites/Player/secondary_black.png",32,51,5,5,5,5,4,4,16);
    sprite.loadAnimation("data/Sprites/Player/secondary.xml");
    sprite.setAnimation(walkStates[currentDir]);
    //sprite.setPosition(96,172);
    sprite.setPosition(2*32,(3*32)+18);
    sprite.setAnimRate(30);
    sprite.setScale(1,1);
    sprite.play();

    dirx = 0; // sprite dir: right (1), left (-1)
    diry = 0; // down (1), up (-1)
    SetTile();
    step->offset = 18;
    this->putBombHandler = putBombHandler;
    bombsLeft = 1;
    bombRadius = 1;
}
void Player::HandleEvents(cgf::InputManager * im){
    if(this->IsDying())
        return;
    dirx = diry = 0;

    int newDir = currentDir;

    if(im->testEvent("left")) {
        dirx = -1;
        newDir = LEFT;
    }

    if(im->testEvent("right")) {

        dirx = 1;
        newDir = RIGHT;
    }

    if(im->testEvent("up")) {
        diry = -1;
        newDir = UP;
    }

    if(im->testEvent("down")) {
        diry = 1;
        newDir = DOWN;
    }

    if(dirx == 0 && diry == 0) {
        if(currentDir < 4)
            currentDir+=4;
        sprite.setAnimation(walkStates[currentDir]);
        sprite.pause();
    }
    else {
        if(currentDir != newDir) {
            sprite.setAnimation(walkStates[newDir]);
            currentDir = newDir;
            sprite.play();
        }
    }
    step->speedX = 100*dirx;
    step->speedY = 100*diry;

    if(im->testEvent("bomb"))
        PutBomb();
}
void Player::PutBomb(){
    if(bombsLeft){
        ((GamePlayState*)putBombHandler)->InsertObjectInGame(new Bomb(floor((step->x+16)/32)*32,floor((step->y+step->offset+16)/32)*32,bombRadius,this,putBombHandler),false);
        bombsLeft--;
    }
}
void Player::GetBomb(){
    bombsLeft++;
}
void Player::Update(cgf::Game* game){
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

void Player::HandleCollision(GameObject* source){
    HandleCollision(source->GetTile());
    if(source->GetType() == ObjectType::Explosion && !this->IsDying())
        this->Destroy();

    if(source->GetType() == ObjectType::Enemy && !this->IsDying())
        this->Destroy();
}

void Player::Destroy(){
    GameObject::Destroy();
    music.openFromFile("data/Effects/bomberman_dying.wav");
    music.setVolume(30);  // 30% do volume máximo
    music.play();
    sprite.setAnimation("death");

}

void Player::HandleCollision(Tile* source){
    AdjustPosition(source);
}
