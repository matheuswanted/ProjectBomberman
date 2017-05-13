#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "GameObject.h"
class Explosion : public GameObject
{
    public:
        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
};
#endif // EXPLOSION_H
