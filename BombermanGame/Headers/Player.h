#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "InputManager.h"
#include "Tile.h"
#include "GameState.h"
class Player : public GameObject
{
    public:
        Player(cgf::GameState * state);
        virtual void HandleEvents(cgf::InputManager * im);
        virtual void Update(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
        virtual void HandleCollision(Tile * tile);
        virtual void Destroy();
        void GetBomb();
    private:

        enum { RIGHT=0, LEFT, UP, DOWN };
        std::string walkStates[8];
        int currentDir;
        int x, y;
        int dirx, diry;
        cgf::GameState * putBombHandler;
        int bombsLeft;
        int bombRadius;

        void PutBomb();
};
#endif // PLAYER_H
