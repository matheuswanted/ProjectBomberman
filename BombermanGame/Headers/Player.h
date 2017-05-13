#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "InputManager.h"
class Player : public GameObject
{
    public:
        Player();
        void HandleEvents(cgf::InputManager * im);
        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);
    private:
        void PutBomb();
};
#endif // PLAYER_H
