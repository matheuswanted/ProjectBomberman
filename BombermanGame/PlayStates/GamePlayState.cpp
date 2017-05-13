#include <vector>
#include "GamePlayState.h"
#include "InputManager.h"

GamePlayState::GamePlayState(){}

void GamePlayState::init()
{
    im = cgf::InputManager::instance();
    objects = new std::vector<GameObject>();
    bombs = new std::vector<GameObject>();
    explosions = new std::vector<GameObject>();

    gameMap = new Map("data/maps","dungeon-tilesets2.tmx");

    player = new Player();

    bomb = new Bomb();

    RegisterEvents();

}
void GamePlayState::cleanup()
{
    delete objects;
    delete bombs;
    delete explosions;
    delete gameMap;
    delete player;
}
void GamePlayState::pause()
{
}
void GamePlayState::resume()
{
}

void GamePlayState::RegisterEvents(){
    im->addKeyInput("quit", sf::Keyboard::Escape);
}

void GamePlayState::handleEvents(cgf::Game *game)
{
    sf::RenderWindow * screen = game->getScreen();
    sf::Event event;

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
    }

    if(im->testEvent("quit"))
        game->quit();

    player->HandleEvents(im);
}
void GamePlayState::update(cgf::Game *game)
{
    CheckDead();
    HandleColissions();
    player->Update(game);
    bomb->Update(game);

    ObjectsUpdateLoop(objects,game);
    ObjectsUpdateLoop(bombs,game);
    ObjectsUpdateLoop(explosions,game);
}

void GamePlayState::draw(cgf::Game *game)
{
    gameMap->Draw(game->getScreen());
    ObjectsDrawLoop(objects,game);
    ObjectsDrawLoop(bombs,game);
    ObjectsDrawLoop(explosions,game);
    player->Draw(game);
    bomb->Draw(game);
}
void GamePlayState::HandleColissions()
{
    std::vector<GameObject>::iterator it = explosions->begin();
    std::vector<GameObject>::iterator objs;

    for (objs = objects->begin(); objs != objects->end(); objs++)
        if (CheckCollision(&(*objs), player))
            player->HandleCollision(&*objs);

    for (; it != explosions->end(); it++)
    {
        player->HandleCollision(&*it);
        for (objs = objects->begin(); objs != objects->end(); objs++)
            if (CheckCollision(&*objs, &*it))
                objs->HandleCollision(&*it);
        for (objs = bombs->begin(); objs != bombs->end(); objs++)
            if (CheckCollision(&*objs, &(*it)))
                objs->HandleCollision(&(*it));
    }
}
int GamePlayState::CheckCollision(GameObject *source, GameObject *dest)
{
    return 0;
}

void GamePlayState::ObjectsDrawLoop(std::vector<GameObject> * objectVector, cgf::Game * game){
    std::vector<GameObject>::iterator objIt = objectVector->begin();

    for (; objIt != objectVector->end(); objIt++)
        objIt->Draw(game);
}

void GamePlayState::ObjectsUpdateLoop(std::vector<GameObject> * objectVector, cgf::Game * game){
    std::vector<GameObject>::iterator objIt = objectVector->begin();

    for (; objIt != objectVector->end(); objIt++)
        objIt->Update(game);
}

void GamePlayState::CheckDead()
{
    RemoveIfDead(objects);
    RemoveIfDead(bombs);
    RemoveIfDead(explosions);
}

void GamePlayState::RemoveIfDead(std::vector<GameObject> * objectVector){
    std::vector<GameObject>::iterator objIt = objectVector->begin();

    for (; objIt != objectVector->end(); objIt++)
        if(objIt->IsDead()) objIt = objectVector->erase(objIt);
}

void GamePlayState::InsertObjectInGame(GameObject *object)
{
    switch(object->objectType){
        case 4://GameObjectType.Bomb:
            bombs->push_back(*object);
            break;
        case 5://GameObjectType.Explosion:
            explosions->push_back(*object);
            break;
        case 6://powerup
            objects->push_back(*object);
        default: break;
    }
}
