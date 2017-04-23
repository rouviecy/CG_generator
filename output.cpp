#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)

#define PORTEE_SHOT 10
#define DIST_MAX 1000
#define CD_MINE 5
#define CD_SHOT 2

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
        InputTurn();
        Action();
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
        Ship()
        void Update(int id, int x, int y, cap, vitesse, rhum);
};

class Barrel : public Entity{
    public:
        int rhum;
        Barrel()
        void Update(int id, int x, int y, rhum);
};

class Ball : public Entity{
    public:
        int idLanceur;
        int cooldown;
        Ball()
        void Update(int id, int x, int y, idLanceur, cooldown);
};

class Mine : public Entity{
    public:
        Mine()
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
    this->cooldownShot = cooldownShot;
    this->cooldownTrap = cooldownTrap;
    this->idBarrelGoal = idBarrelGoal;
}

void Ship::Update(int id, int x, int y, cap, vitesse, rhum){
    Entity::Update(id, x, y);
    this->cap = cap;
    this->vitesse = vitesse;
    this->rhum = rhum;
}

Barrel::Barrel() : Entity(){
}

void Barrel::Update(int id, int x, int y, rhum){
    Entity::Update(id, x, y);
    this->rhum = rhum;
}

Ball::Ball() : Entity(){
}

void Ball::Update(int id, int x, int y, idLanceur, cooldown){
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
    map <int, bool> shipsStillExists;
    map <int, bool> barrelsStillExists;
    map <int, bool> ballsStillExists;
    map <int, bool> minesStillExists;
    cin >> teamSize >> nbEntities ; cin.ignore;
    for(int i = 0; i < 4; i++){
        int id, int x, int y, int arg0, int arg1, int arg2, int arg3;
        string entityType;        cin >> id >> entityType >> x >> y>> arg0 >> arg1 >> arg2 >> arg3 ;
        if(false){}
        else if(entityType.compare(SHIP) == 0){
            if(ships.find(id) == ships.end()){ships[id] = Ship();}
            ships[id].Update(id, x, y, cap, vitesse, rhum);
            shipsStillExists[id] = true;
        else if(entityType.compare(BARREL) == 0){
            if(barrels.find(id) == barrels.end()){barrels[id] = Barrel();}
            barrels[id].Update(id, x, y, rhum);
            barrelsStillExists[id] = true;
        else if(entityType.compare(CANNONBALL) == 0){
            if(balls.find(id) == balls.end()){balls[id] = Ball();}
            balls[id].Update(id, x, y, idLanceur, cooldown);
            ballsStillExists[id] = true;
        else if(entityType.compare(MINE) == 0){
            if(mines.find(id) == mines.end()){mines[id] = Mine();}
            mines[id].Update(id, x, y);
            minesStillExists[id] = true;
        }
    }
    forMap(int, Ship, it, ships){
        if(shipsStillExists.find(it->first) == shipsStillExists.end()){it = ships.erase(it);}
        else{++it;}
    }
    forMap(int, Barrel, it, barrels){
        if(barrelsStillExists.find(it->first) == barrelsStillExists.end()){it = barrels.erase(it);}
        else{++it;}
    }
    forMap(int, Ball, it, balls){
        if(ballsStillExists.find(it->first) == ballsStillExists.end()){it = balls.erase(it);}
        else{++it;}
    }
    forMap(int, Mine, it, mines){
        if(minesStillExists.find(it->first) == minesStillExists.end()){it = mines.erase(it);}
        else{++it;}
    }
}

void Game::Action(){
    // Inserer ici les operations utiles pour chaque tour
}

int main(){
    Game game;
    while(1){
        game.InputTurn();
        game.Action();
}
