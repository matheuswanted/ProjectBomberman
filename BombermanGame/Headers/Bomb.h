
#ifndef BOMB_H
#define BOMB_H
#include "GameObject.h"
#include "InputManager.h"

class Bomb : public GameObject
{
    public:
        Bomb(int x, int y);
        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);

    sf::RenderWindow* screen;
};
#endif // BOMB_H

