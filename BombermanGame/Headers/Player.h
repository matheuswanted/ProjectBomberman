#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "InputManager.h"
#include "Tile.h"
class Player : public GameObject
{
    public:
        Player();
        void HandleEvents(cgf::InputManager * im);
        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
        virtual void HandleCollision(Tile * tile);
    private:

        enum { RIGHT=0, LEFT, UP, DOWN };
        std::string walkStates[4];
        int currentDir;

        int x, y;
        int dirx, diry;

        void PutBomb();
};
#endif // PLAYER_H
