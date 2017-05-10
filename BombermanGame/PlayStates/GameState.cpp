void GameState::init()
{
    im = cgf::InputManager::instance();
}
void GameState::cleanup()
{
}
void GameState::pause()
{
}
void GameState::resume()
{
}
void GameState::handleEvents(Game *game)
{

    player.HandleEvents(&im);
}
void GameState::update(Game *game)
{
    map.Update(game);
    HandleColissions();
    player.Update(game);
    std::vector<GameObject>::iterator objs = 0;
    for (objs = objects.begin(); objs != objects.end(); objs++)
        objs.Update(game);
    for (objs = bombs.begin(); objs != objects.end(); objs++)
        objs.Update(game);
    for (objs = explosions.begin(); objs != objects.end(); objs++)
        objs.Update(game);
}
void GameState::draw(Game *game)
{
    map.Draw(game);
    std::vector<GameObject>::iterator objs = 0;
    for (objs = objects.begin(); objs != objects.end(); objs++)
        objs.Draw(game);
    for (objs = explosions.begin(); objs != objects.end(); objs++)
        objs.Draw(game);
    player.Draw(game);
}
void GameState::HandleColissions()
{
    std::vector<GameObject>::iterator it = explosions.begin();
    std::vector<GameObject>::iterator objs = 0;

    for (objs = objects.begin(); objs != objects.end(); objs++)
        if (CheckCollision(objs, &player))
            player.HandleCollision(objs);

    for (; it != explosions.end(); it++)
    {
        player.HandleCollision(it);
        for (objs = objects.begin(); objs != objects.end(); objs++)
            if (CheckCollision(objs, &it))
                objs.HandleCollision(it);
        for (objs = bombs.begin(); objs != bombs.end(); objs++)
            if (CheckCollision(objs, &it))
                objs.HandleCollision(it);
    }
}
int GameState::CheckCollision(GameObject *source, GameObject *dest)
{
    return 0;
}

void InsertObjectInGame(GameObject *object)
{
    switch(object->objectType){
        case GameObjectType.Bomb:
            bombs.put(*object);
            break;
        case GameObjectType.Explosion:
            explosions.put(*object);
            break;
        default: break;
    }
}
