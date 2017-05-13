#ifndef GAME_PLAY_STATE_H
#define GAME_PLAY_STATE_H
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "Explosion.h"

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

    int CheckCollision(GameObject * source, GameObject * dest);

    void HandleColissions();

    void InsertObjectInGame(GameObject * object);

    private:
    Map* gameMap;
    Player* player;
    std::vector<GameObject> * objects;
    std::vector<GameObject> * bombs;
    std::vector<GameObject> * explosions;
    cgf::InputManager * im;
    void RegisterEvents();

    void ObjectsDrawLoop(std::vector<GameObject> * objectVector, cgf::Game * game);
    void ObjectsUpdateLoop(std::vector<GameObject> * objectVector, cgf::Game * game);
    void RemoveIfDead(std::vector<GameObject> * objectVector);
    void CheckDead();
};

#endif
