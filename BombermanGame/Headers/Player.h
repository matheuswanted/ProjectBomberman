#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
class Player : GameObject
{
    public:
        Player();
        void HandleEvents(cgf::InputManager * im);
    private:
        void PutBomb();
};
#endif // PLAYER_H
