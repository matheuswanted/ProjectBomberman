#include "GameObject.h"


GameObject::GameObject(){

}

void GameObject::DecreaseLife(int damage){

}
void GameObject::Draw(cgf::Game* game){

}
void GameObject::HandleCollision(GameObject * source){}

void GameObject::HandleCollision(Tile* source){

}
void GameObject::Move(int direction){}

void GameObject::Update(cgf::Game * game){}

bool GameObject::IsDead(){
    return lifePoints == 0;
}

void GameObject::Step(){

}

Tile* GameObject::GetTile(){
    return step;
}
ObjectType GameObject::GetType(){

};
