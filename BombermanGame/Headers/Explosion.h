#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <vector>
#include "GameObject.h"

class Explosion : public GameObject
{
    public:
        Explosion(float x, float y,int side, bool isEnd);
        virtual void Update(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
        virtual void HandleCollision(Tile * tile);
};
#endif // EXPLOSION_H
