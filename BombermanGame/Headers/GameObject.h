#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameState.h"
#include "Sprite.h"
/*enum GameObjectType
{
    Player, Wall, Monster, Bomb, Explosion
};*/
class GameObject
{
    public:
        /// 1 - Player / 2 - Wall / 3 - Monster / 4 - Bomb
        int objectType;
        int objectOwnerId;
        int lifePoints;
        int tileId;

        GameObject();
        GameObject(int ownerId);

        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject* source);

        bool IsDead();

    protected:
        cgf::Sprite sprite;
        virtual void DecreaseLife(int damage);
        virtual void Move(int direction);

};
#endif // GAMEOBJECT_H

