#ifndef BOMB_H
#define BOMB_H
#include "GameObject.h"

class Bomb : public GameObject
{
    public:
        Bomb(int x, int y);
        Bomb(int x, int y,int radius, GameObject * player, cgf::GameState * explosionHandler);
        virtual void Update(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);

    private:
        GameObject * player = NULL;
        cgf::GameState * explosionHandler = NULL;
        void Explode();
        int radius;
};
#endif // BOMB_H

