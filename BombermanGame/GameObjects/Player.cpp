#include "Player.h"
Player::Player(){
    sprite.load("data/Sprites/Player/player.png",32,49,0,0,0,0,12,1,12);
    sprite.setCurrentFrame(0);
    sprite.setPosition(40,100);
}
void Player::HandleEvents(cgf::InputManager * im){
}
void Player::PutBomb(){
}
void Player::Update(cgf::Game* game){

}
void Player::Draw(cgf::Game* game){
    game->getScreen()->draw(sprite);
}
void Player::HandleCollision(GameObject* source){

}

void Player::HandleCollision(Tile* source){

}
