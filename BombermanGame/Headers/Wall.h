#ifndef WALL_H
#define WALL_H
#include "GameObject.h"
class Wall : public GameObject
{
    public:
        Wall(int x, int y);
        virtual void Update(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
        virtual void Destroy();
};
#endif // BOMB_H
