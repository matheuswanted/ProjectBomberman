#include <vector>
#include "GamePlayState.h"
#include "InputManager.h"

#define TILE_SIZE 32

GamePlayState::GamePlayState(){}

void GamePlayState::init()
{
    im = cgf::InputManager::instance();
    movingObjects = new std::vector<GameObject*>();
    staticObjects = new std::vector<GameObject*>();
    explosions = new std::vector<GameObject*>();

    gameMap = new Map("data/maps","bomberman_stage_1.tmx");

    player = new Player();

    staticObjects->push_back(new Bomb(100,100));

    RegisterEvents();

}
void GamePlayState::cleanup()
{
    delete staticObjects;
    delete movingObjects;
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
    im->addKeyInput("left", sf::Keyboard::Left);
    im->addKeyInput("right", sf::Keyboard::Right);
    im->addKeyInput("up", sf::Keyboard::Up);
    im->addKeyInput("down", sf::Keyboard::Down);
    im->addKeyInput("bomb", sf::Keyboard::Space);
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
    HandleColisions();
    player->Update(game);

    ObjectsUpdateLoop(staticObjects,game);
    ObjectsUpdateLoop(movingObjects,game);
    ObjectsUpdateLoop(explosions,game);
}

void GamePlayState::draw(cgf::Game *game)
{
    gameMap->Draw(game->getScreen());
    ObjectsDrawLoop(staticObjects,game);
    ObjectsDrawLoop(movingObjects,game);
    ObjectsDrawLoop(explosions,game);
    player->Draw(game);
}
void GamePlayState::HandleColisions()
{
    std::vector<GameObject*>::iterator objectIt = movingObjects->begin();

    //CollisionCheckWithWalls
    //TODO
    CheckLoopCollision(player,staticObjects);

    //Collision of moving objects
    for (; objectIt != movingObjects->end(); objectIt++){
        if(CheckMapCollision(*objectIt))
            (*objectIt)->HandleCollision(*objectIt);

        CheckLoopCollision(*objectIt,staticObjects);

        if (CheckCollision((*objectIt)->GetTile(), player->GetTile())){
            player->HandleCollision(*objectIt);
            (*objectIt)->HandleCollision(player);
        }
    }


    objectIt = explosions->begin();
    for (; objectIt != explosions->end(); objectIt++)
    {
        ((Explosion*)*objectIt)->CheckBoundariesCollision(staticObjects);
        ((Explosion*)*objectIt)->CheckBoundariesCollision(movingObjects);

        if (CheckCollision(player->GetTile(), (*objectIt)->GetTile()))
            player->HandleCollision(*objectIt);
    }
}
bool GamePlayState::CheckMapCollision(GameObject * source){
    Tile * tile = source->GetTile();
    Tile * tileMap = gameMap->GetCellFromMap(tile->x,tile->y);
    if(tileMap){
        source->HandleCollision(tileMap);
        delete tileMap;
    }
}

void GamePlayState::CheckLoopCollision(GameObject* src, std::vector<GameObject*> * objectVector){
    std::vector<GameObject*>::iterator innerIt = objectVector->begin();
    for (; innerIt != objectVector->end(); innerIt++){
        if (CheckCollision(src->GetTile(), (*innerIt)->GetTile())){
            src->HandleCollision(*innerIt);
        }
    }
}


bool GamePlayState::CheckCollision(Tile *source, Tile *dest)
{
    float x1min, y1min, x2max, y2max;
    float x1max, y1max, x2min, y2min;
    //obj1 min point
    x1min = source->x;
    x2max = dest->x + dest->width;

    x1max = source->x + source->width;
    y1max = source->y + source->height + source->offset;


    //obj2 max point
    y1min = source->y + source->offset;
    y2max = dest->y + dest->height + dest->offset;

    x2min = dest->x;
    y2min = dest->y + dest->offset;


    if(x1max>x2min && x1min<x2max && y1max >y2min && y1min<y2max)
        return true;

    return false;
}


void GamePlayState::ObjectsDrawLoop(std::vector<GameObject*> * objectVector, cgf::Game * game){
    std::vector<GameObject*>::iterator objIt = objectVector->begin();

    for (; objIt != objectVector->end(); objIt++)
        (*objIt)->Draw(game);
}

void GamePlayState::ObjectsUpdateLoop(std::vector<GameObject*> * objectVector, cgf::Game * game){
    std::vector<GameObject*>::iterator objIt = objectVector->begin();

    for (; objIt != objectVector->end(); objIt++)
        (*objIt)->Update(game);
}

void GamePlayState::CheckDead()
{
    RemoveIfDead(staticObjects);
    RemoveIfDead(movingObjects);
    RemoveIfDead(explosions);
}

void GamePlayState::RemoveIfDead(std::vector<GameObject*> * objectVector){
    std::vector<GameObject*>::iterator objIt = objectVector->begin();

    for (; objIt != objectVector->end(); objIt++)
        if((*objIt)->IsDead()) objIt = objectVector->erase(objIt);
}

void GamePlayState::InsertObjectInGame(GameObject *object){
    switch(object->GetType()){
        case ObjectType::Bomb://GameObjectType.Bomb:
            staticObjects->push_back(object);
            break;
        case ObjectType::Explosion://GameObjectType.Explosion:
            explosions->push_back(object);
            break;
        default: break;
    }
}
