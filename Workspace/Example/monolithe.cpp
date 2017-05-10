#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
class Game;
class Entity;
class Ship;
class Barrel;
class Ball;
class Mine;
class Entity_readonly{
    public:
        int id;
        int x;
        int y;
        Entity_readonly();
        Entity_readonly(int id, int x, int y);
        void Update(int id, int x, int y);
};
class Entity : public Entity_readonly{
    public:
        Entity();
        Entity(int id, int x, int y);
        void Update(int id, int x, int y);
    private:
};
class Ship_readonly : public Entity{
    public:
        int cap;
        int vitesse;
        int rhum;
        int cooldownShot;
        int cooldownTrap;
        int idBarrelGoal;
        Ship_readonly();
        void Update(int id, int x, int y, int cap, int vitesse, int rhum);
};
class Ship : public Ship_readonly{
    public:
        Ship();
    private:
};
class Barrel_readonly : public Entity{
    public:
        int rhum;
        Barrel_readonly();
        void Update(int id, int x, int y, int rhum);
};
class Barrel : public Barrel_readonly{
    public:
        Barrel();
    private:
};
class Ball_readonly : public Entity{
    public:
        int idLanceur;
        int cooldown;
        Ball_readonly();
        void Update(int id, int x, int y, int idLanceur, int cooldown);
};
class Ball : public Ball_readonly{
    public:
        Ball();
    private:
};
class Mine_readonly : public Entity{
    public:
        Mine_readonly();
        void Update(int id, int x, int y);
};
class Mine : public Mine_readonly{
    public:
        Mine();
    private:
};
class Game_readonly{
    public:
        map <int, Ship> ships;
        map <int, Barrel> barrels;
        map <int, Ball> balls;
        map <int, Mine> mines;
        Game_readonly();
        void InputTurn();
        void Action();
    private:
        template <class EntityType> void DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists);
        template <class EntityType> void RefreshDico(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists, int id);
};
class Game : public Game_readonly{
    public:
        Game();
        void InputTurn();
        void Action();
    private:
};
Game::Game() : Game_readonly(){
}
void Game::InputTurn(){
    Game_readonly::InputTurn();
}
void Game::Action(){
    Game_readonly::Action();
}
Game_readonly::Game_readonly(){
}
void Game_readonly::InputTurn(){
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
void Game_readonly::Action(){
}
template <class EntityType> void Game_readonly::DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists){
    for(typename map<int,EntityType>::iterator it = (*dicoToClean).begin(); it != (*dicoToClean).end(); ++it){
        if(dicoStillExists->find(it->first) == dicoStillExists->end()){it = dicoToClean->erase(it);}
        else{++it;}
    }
}
template <class EntityType> void Game_readonly::RefreshDico(map <int, EntityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id){
    if(dicoToRefresh->find(id) == dicoToRefresh->end()){(*dicoToRefresh)[id] = EntityType();}
    (*dicoStillExists)[id] = true;
}
Entity::Entity() : Entity_readonly(){}
Entity::Entity(int id, int x, int y) : Entity_readonly(id, x, y){
}
void Entity::Update(int id, int x, int y){
    Entity_readonly::Update(id, x, y);
}
Entity_readonly::Entity_readonly() : Entity_readonly(-1, 0, 0){}
Entity_readonly::Entity_readonly(int id, int x, int y){
    Entity_readonly::Update(id, x, y);
}
void Entity_readonly::Update(int id, int x, int y){
    this->id = id;
    this->x = x;
    this->y = y;
}
Ship::Ship() : Ship_readonly(){
}
Ship_readonly::Ship_readonly() : Entity(){
    this->cooldownShot = 0;
    this->cooldownTrap = 0;
    this->idBarrelGoal = 0;
}
void Ship_readonly::Update(int id, int x, int y, int cap, int vitesse, int rhum){
    Entity::Update(id, x, y);
    this->cap = cap;
    this->vitesse = vitesse;
    this->rhum = rhum;
};
Barrel::Barrel() : Barrel_readonly(){
}
Barrel_readonly::Barrel_readonly() : Entity(){
}
void Barrel_readonly::Update(int id, int x, int y, int rhum){
    Entity::Update(id, x, y);
    this->rhum = rhum;
};
Ball::Ball() : Ball_readonly(){
}
Ball_readonly::Ball_readonly() : Entity(){
}
void Ball_readonly::Update(int id, int x, int y, int idLanceur, int cooldown){
    Entity::Update(id, x, y);
    this->idLanceur = idLanceur;
    this->cooldown = cooldown;
};
Mine::Mine() : Mine_readonly(){
}
Mine_readonly::Mine_readonly() : Entity(){
}
void Mine_readonly::Update(int id, int x, int y){
    Entity::Update(id, x, y);
};
int main(){
    Game game;
    while(1){
        game.InputTurn();
        game.Action();
    }
}
