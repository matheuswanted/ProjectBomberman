#ifndef MAPENEMY_H
#define MAPENEMY_H

#include "GameObject.h"
#include "Tile.h"
#include "GameState.h"

class MapEnemy : public GameObject
{
    public:
        MapEnemy(cgf::GameState * state, int x, int y);
        virtual void Update(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
        virtual void HandleCollision(Tile * tile);
        virtual void Destroy();

    private:

        enum { RIGHT=0, LEFT, UP, DOWN };
        std::string walkStates[8];
        int currentDir;
        int x, y;
        int dirx, diry;
};

#endif // MAPENEMY_H
