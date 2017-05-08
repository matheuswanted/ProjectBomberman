#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Sprite.h"
#include "GameState.h"
class GameObject
{
    public:
        /// 1 - Player / 2 - Wall / 3 - Monster / 4 - Bomb
        GameObjectType objectType;
        int objectOwnerId;
        int lifePoints;
        int tileId;

        GameObject();
        GameObject(int ownerId);

        virtual void Update();
        virtual void Draw();
        virtual void HandleCollision(GameObject* source);

    protected:
        cgf::Sprite sprite;
        virtual void DecreaseLife(int damage);
        virtual void Move(int direction);
};
enum GameObjectType
{
    Player, Wall, Monster, Bomb
};
#endif // GAMEOBJECT_H

