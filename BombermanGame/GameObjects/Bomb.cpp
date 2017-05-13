
#include "Bomb.h"

using namespace std;

Bomb::Bomb(){
    sprite.load("../bin/data/Sprites/Bombs/bomb.png", 32, 32, 5, 5, 5, 5, 6, 1, 6);
    sprite.loadAnimation("../bin/data/Sprites/Bombs/bomb_anim.xml");
    sprite.setPosition(0, 0);
    sprite.setAnimation("explode");
    sprite.setAnimRate(2);
    sprite.play();
}

void Bomb::Update(cgf::Game* game) {
    sprite.update(game->getUpdateInterval());
}

void Bomb::Draw(cgf::Game* game) {
    screen = game->getScreen();
    screen->draw(sprite);
}

void Bomb::HandleCollision(GameObject* source){

}
