#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "ObjectType.h"
#include "GameState.h"
#include "Sprite.h"
#include "Tile.h"
class GameObject
{
    public:
        int lifePoints;
        GameObject();
        GameObject(int ownerId);

        virtual void Update(cgf::Game* game);
        virtual void Draw(cgf::Game* game);
        virtual void HandleCollision(GameObject * obj);
        virtual void HandleCollision(Tile * tile);
        Tile * GetTile();
        ObjectType GetType();

        bool IsDead();

    protected:
        cgf::Sprite sprite;
        ObjectType type;
        Tile * step = new Tile();
        virtual void DecreaseLife(int damage);
        virtual void Move(int direction);
        virtual void Step(double interval);
        void SetTile();
        void AdjustPosition(Tile * tile);
};
#endif // GAMEOBJECT_H

