#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)
#define forMapTypename(type1, type2, it, carte) for(typename map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)

#define CD_MINE 5
#define CD_SHOT 2
#define PORTEE_SHOT 10
#define DIST_MAX 1000

class Game;
class Entity;
class Ship;
class Barrel;
class Ball;
class Mine;

class Game{
    public:
        map <int, Ship> ships;
        map <int, Barrel> barrels;
        map <int, Ball> balls;
        map <int, Mine> mines;
        Game();
        void InputTurn();
        void Action();
    private:
        template <class EntityType> void DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists);
        template <class EntityType> void RefreshDico(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists, int id);
};

class Entity{
    public:
        int id;
        int x;
        int y;
        Entity();
        Entity(int id, int x, int y);
        void Update(int id, int x, int y);
};

class Ship : public Entity{
    public:
        int cap;
        int vitesse;
        int rhum;
        int cooldownShot;
        int cooldownTrap;
        int idBarrelGoal;
        Ship();
        void Update(int id, int x, int y, int cap, int vitesse, int rhum);
};

class Barrel : public Entity{
    public:
        int rhum;
        Barrel();
        void Update(int id, int x, int y, int rhum);
};

class Ball : public Entity{
    public:
        int idLanceur;
        int cooldown;
        Ball();
        void Update(int id, int x, int y, int idLanceur, int cooldown);
};

class Mine : public Entity{
    public:
        Mine();
        void Update(int id, int x, int y);
};

Entity::Entity() : Entity(-1, 0, 0){}

Entity::Entity(int id, int x, int y){
    Entity::Update(id, x, y);
}

void Entity::Update(int id, int x, int y){
    this->id = id;
    this->x = x;
    this->y = y;
}

Ship::Ship() : Entity(){
    this->cooldownShot = 0;
    this->cooldownTrap = 0;
    this->idBarrelGoal = 0;
}

void Ship::Update(int id, int x, int y, int cap, int vitesse, int rhum){
    Entity::Update(id, x, y);
    this->cap = cap;
    this->vitesse = vitesse;
    this->rhum = rhum;
}

Barrel::Barrel() : Entity(){
}

void Barrel::Update(int id, int x, int y, int rhum){
    Entity::Update(id, x, y);
    this->rhum = rhum;
}

Ball::Ball() : Entity(){
}

void Ball::Update(int id, int x, int y, int idLanceur, int cooldown){
    Entity::Update(id, x, y);
    this->idLanceur = idLanceur;
    this->cooldown = cooldown;
}

Mine::Mine() : Entity(){
}

void Mine::Update(int id, int x, int y){
    Entity::Update(id, x, y);
}

Game::Game(){
}

void Game::InputTurn(){
    map <int, bool> shipsStillExists, barrelsStillExists, ballsStillExists, minesStillExists;
    int teamSize, nbEntities;
    cin >> teamSize >> nbEntities; cin.ignore();
    for(int i = 0; i < 4; i++){
        int id, x, y, arg1, arg2, arg3, arg4;
        string entityType;
        cin >> id >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
        if(false){}
        else if(entityType.compare("SHIP") == 0){
            ships[id].Update(id, x, y, arg1, arg2, arg3);
            RefreshDico<Ship>(&ships, &shipsStillExists, id);
        }
        else if(entityType.compare("BARREL") == 0){
            barrels[id].Update(id, x, y, arg1);
            RefreshDico<Barrel>(&barrels, &barrelsStillExists, id);
        }
        else if(entityType.compare("CANNONBALL") == 0){
            balls[id].Update(id, x, y, arg1, arg2);
            RefreshDico<Ball>(&balls, &ballsStillExists, id);
        }
        else if(entityType.compare("MINE") == 0){
            mines[id].Update(id, x, y);
            RefreshDico<Mine>(&mines, &minesStillExists, id);
        }
    }
    DeleteObsoleteEntities<Ship>(&ships, &shipsStillExists);
    DeleteObsoleteEntities<Barrel>(&barrels, &barrelsStillExists);
    DeleteObsoleteEntities<Ball>(&balls, &ballsStillExists);
    DeleteObsoleteEntities<Mine>(&mines, &minesStillExists);
}

void Game::Action(){
    // Inserer ici les operations utiles pour chaque tour
}

template <class EntityType> void Game::DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists){
    forMapTypename(int, EntityType, it, (*dicoToClean)){
        if(dicoStillExists->find(it->first) == dicoStillExists->end()){it = dicoToClean->erase(it);}
        else{++it;}
    }
}

template <class EntityType> void Game::RefreshDico(map <int, EntityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id){
    if(dicoToRefresh->find(id) == dicoToRefresh->end()){(*dicoToRefresh)[id] = EntityType();}
    (*dicoStillExists)[id] = true;
}

int main(){
    Game game;
    while(1){
        game.InputTurn();
        game.Action();
    }
}

