#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
class Player : GameObject
{
    public:
        Player();
        void HandleKeyPress(char key);
    private:
        void PutBomb();
};
#endif // PLAYER_H
