#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <vector>
#include "GameObject.h"

class Explosion : public GameObject
{
    public:
        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
        virtual void HandleCollision(Tile * tile);
        virtual void CheckBoundariesCollision(std::vector<GameObject*> * objects);
};
#endif // EXPLOSION_H
