#include "Player.h"
#include<iostream>

using namespace std;

Player::Player(){

    type = ObjectType::Player;
    walkStates[0] = "right";
    walkStates[1] = "left";
    walkStates[2] = "up";
    walkStates[3] = "down";

    currentDir = DOWN;

    //sprite.load("data/Sprites/Player/player.png",32,49,0,0,0,0,1,12,12);
    //sprite.loadAnimation("data/Sprites/Player/playeranim.xml");
    sprite.load("data/Sprites/Player/secondary_black.png",32,51,5,5,5,5,4,4,16);
    sprite.loadAnimation("data/Sprites/Player/secondary.xml");
    sprite.setAnimation(walkStates[currentDir]);
    sprite.setPosition(64,140);
    sprite.setAnimRate(30);
    sprite.setScale(1,1);
    sprite.play();

    dirx = 0; // sprite dir: right (1), left (-1)
    diry = 0; // down (1), up (-1)
    SetTile();
    step->offset = 18;
}
void Player::HandleEvents(cgf::InputManager * im){

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
        sprite.pause();
    }
    else {
        if(currentDir != newDir) {
            sprite.setAnimation(walkStates[newDir]);
            currentDir = newDir;
        }
        sprite.play();
    }
    step->speedX = 100*dirx;
    step->speedY = 100*diry;
}
void Player::PutBomb(){
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

void Player::Draw(cgf::Game* game){
    game->getScreen()->draw(sprite);
}
void Player::HandleCollision(GameObject* source){
    HandleCollision(source->GetTile());
}

void Player::HandleCollision(Tile* source){
    AdjustPosition(source);
}
