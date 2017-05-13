#ifndef GAME_PLAY_STATE_H
#define GAME_PLAY_STATE_H
#include <vector>
#include "Player.h"
#include "GameState.h"
#include "GameObject.h"
#include "Map.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Tile.h"

class GamePlayState : public cgf::GameState
{
    public:

    GamePlayState();

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    void HandleColisions();

    void InsertObjectInGame(GameObject * object);

    private:
    Map* gameMap;
    Player* player;
    std::vector<GameObject*> * movingObjects;
    std::vector<GameObject*> * staticObjects;
    std::vector<GameObject*> * explosions;
    cgf::InputManager * im;
    void RegisterEvents();
    void CheckLoopCollision(GameObject* src, std::vector<GameObject*> * objectVector);
    void ObjectsDrawLoop(std::vector<GameObject*> * objectVector, cgf::Game * game);
    void ObjectsUpdateLoop(std::vector<GameObject*> * objectVector, cgf::Game * game);
    void RemoveIfDead(std::vector<GameObject*> * objectVector);
    void CheckDead();
    bool CheckCollision(Tile * source, Tile * dest);
    bool CheckMapCollision(GameObject * source);
};

#endif
