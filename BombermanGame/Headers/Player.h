#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "InputManager.h"
class Player : public GameObject
{
    public:
        Player();
        void HandleEvents(cgf::InputManager * im);
    private:
        void PutBomb();
};
#endif // PLAYER_H
