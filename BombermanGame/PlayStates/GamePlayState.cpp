#include <vector>
#include "GamePlayState.h"
#include "InputManager.h"

#define TILE_SIZE 32

GamePlayState::GamePlayState(){}

void GamePlayState::init()
{
    im = cgf::InputManager::instance();
    movingObjects = new std::vector<GameObject*>();
    staticObjectsMap = new std::map<int,GameObject*>();

    gameMap = new Map("data/maps","bomberman_stage_1.tmx");

    player = new Player(this);
    CreateWalls();
    RegisterEvents();

}

void GamePlayState::CreateWalls(){
    int * arrayIt= new int[92]{
        3,5,7,8,9,-1,
        2,4,6,8,10,-1,
        1,2,3,4,5,6,7,8,10,11,-1,
        0,2,4,6,8,10,12,-1,
        0,1,2,3,4,5,6,7,8,10,11,12,-1,
        2,6,8,10,-1,
        0,1,2,3,4,5,6,8,10,11,12,-1,
        0,2,4,6,8,10,12,-1,
        1,2,3,4,5,6,7,8,9,11,-1,
        2,4,6,8,10,-1,
        3,4,6,8,9
    };
    int rowCont = gameMap->GetRowCont();
    int row = 0;
    int i = 0;
    int key = 0;
    for (;i<92;i++){
        if(arrayIt[i] == -1)
            row++;
        else{
            key = (row+4)*rowCont + 2+arrayIt[i];
            staticObjectsMap->insert(std::make_pair(key,new Wall((2+arrayIt[i])*32,(4+row)*32)));
        }
    }
}

void GamePlayState::cleanup()
{
    delete movingObjects;
    delete gameMap;
    delete player;
    delete staticObjectsMap;
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
    HandleCollisions();
    player->Update(game);
    std::map<int,GameObject*>::iterator objectIt = staticObjectsMap->begin();
    for(;objectIt != staticObjectsMap->end();objectIt++){
        (objectIt->second)->Update(game);
    }
    std::vector<GameObject*>::iterator objIt = movingObjects->begin();
    for (; objIt != movingObjects->end(); objIt++)
        (*objIt)->Update(game);
}

void GamePlayState::draw(cgf::Game *game)
{
    gameMap->Draw(game->getScreen());

    std::map<int,GameObject*>::iterator objectIt = staticObjectsMap->begin();
    for(;objectIt != staticObjectsMap->end();objectIt++)
        (objectIt->second)->Draw(game);

    std::vector<GameObject*>::iterator objIt = movingObjects->begin();
    for (; objIt != movingObjects->end(); objIt++)
        (*objIt)->Draw(game);

    player->Draw(game);
}
void GamePlayState::HandleCollisions()
{
    std::vector<GameObject*>::iterator objectIt = movingObjects->begin();
    //CollisionCheckWithWalls
    //TODO
    CheckMapCollision(player);
    //Collision of moving objects
    for (; objectIt != movingObjects->end(); objectIt++){
        CheckMapCollision(*objectIt);
        if (CheckCollision((*objectIt)->GetTile(), player->GetTile())){
            player->HandleCollision(*objectIt);
            (*objectIt)->HandleCollision(player);
        }
    }
}
bool GamePlayState::CheckMapCollision(GameObject * source){
    Tile * tile = source->GetTile();

    float x, y;
    x = tile->x;
    y = tile->y+tile->offset;

    int rowCont = gameMap->GetRowCont();

    Tile ** tileMap = gameMap->GetPossibleCellCollisionsFromMap(x,y);
    Tile * forDelete;
    int i;
    for(i = 0;i<4;i++){
        if(*tileMap != NULL){
            source->HandleCollision(*tileMap);
            forDelete = *tileMap;

            delete forDelete;
        }
        tileMap++;
    }
    int key = floor(y/32)*rowCont + floor(x/32);
    if(staticObjectsMap->count(key) >0)
        source->HandleCollision(staticObjectsMap->find(key)->second);

    key = floor((y+32)/32)*rowCont + floor((x+32)/32);
    if(staticObjectsMap->count(key) >0)
        source->HandleCollision(staticObjectsMap->find(key)->second);


    key = floor((y+32)/32)*rowCont + floor(x/32);
    if(staticObjectsMap->count(key) >0)
        source->HandleCollision(staticObjectsMap->find(key)->second);


    key = floor(y/32)*rowCont + floor((x+32)/32);
    if(staticObjectsMap->count(key) >0)
        source->HandleCollision(staticObjectsMap->find(key)->second);



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

void GamePlayState::CheckDead()
{
    RemoveIfDead(staticObjectsMap);
    RemoveIfDead(movingObjects);
}

void GamePlayState::RemoveIfDead(std::map<int,GameObject*> * objectVector){
    std::map<int,GameObject*>::iterator objIt = objectVector->begin();

    while (objIt != objectVector->end())
        if((objIt->second)->IsDead())
            objIt = objectVector->erase(objIt);
        else
            objIt++;
}

void GamePlayState::RemoveIfDead(std::vector<GameObject*> * objectVector){
    std::vector<GameObject*>::iterator objIt = objectVector->begin();

    while (objIt != objectVector->end())
        if((*objIt)->IsDead())
            objIt = objectVector->erase(objIt);
        else
            objIt++;
}

bool GamePlayState::InsertObjectInGame(GameObject *object, bool overwriteCell){
    int key = floor(object->GetTile()->y/32)*gameMap->GetRowCont() + floor(object->GetTile()->x/32);
    switch(object->GetType()){
        case ObjectType::Bomb://GameObjectType.Bomb:
            staticObjectsMap->insert(std::make_pair(key,object));
            break;
        case ObjectType::Explosion://GameObjectType.Explosion:
            if(gameMap->HasWallOnCell(object->GetTile()->x,object->GetTile()->y))
                return false;
            if(!overwriteCell && staticObjectsMap->find(key) != staticObjectsMap->end()){
                    (*staticObjectsMap)[key]->Destroy();
                return false;
            }
            (*staticObjectsMap)[key] = object;
            break;
        default: break;
    }
    return true;
}
