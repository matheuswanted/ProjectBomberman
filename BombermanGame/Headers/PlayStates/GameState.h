#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include "GameState.h"

class GameState : public cgf::GameState
{
    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(Game* game);
    void update(Game* game);
    void draw(Game* game);

    void CheckCollision(GameObject * source, GameObject * dest);

    void HandleColissions();

    void InsertObjectInGame(GameObject * object);

    private:
    Map map;
    Player player;
    vector<GameObject> objects;
    vector<GameObject> bombs;
    vector<Explosion> explosions;
    cgf::InputManager im;
};

#endif