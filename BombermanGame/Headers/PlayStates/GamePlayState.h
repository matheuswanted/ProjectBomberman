#ifndef GAME_PLAY_STATE_H
#define GAME_PLAY_STATE_H
#include <vector>
#include <map>
#include "Player.h"
#include "GameState.h"
#include "GameObject.h"
#include "Map.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Wall.h"
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

    void HandleCollisions();

    bool InsertObjectInGame(GameObject * object, bool overwriteCell);

    private:
    Map* gameMap;
    Player* player;
    std::map<int,GameObject*> * staticObjectsMap;
    std::vector<GameObject*> * movingObjects;
    cgf::InputManager * im;
    void RegisterEvents();
    void RemoveIfDead(std::vector<GameObject*> * objectVector);
    void RemoveIfDead(std::map<int,GameObject*> * objectVector);
    void CheckDead();
    bool CheckCollision(Tile * source, Tile * dest);
    bool CheckMapCollision(GameObject * source);
    void CreateWalls();
};

#endif
