#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)

#define CD_SHOT     2
#define CD_MINE     5
#define DIST_MAX    1000
#define PORTEE_SHOT 10

class Game;
class Entity;
class Ship;
class Barrel;
class Ball;
class Mine;
class Utils;

class Utils{
    public:
        static int Distance(int x1, int y1, int x2, int y2);
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
        void Goto(int x, int y);
        void Wait();
        void Slow();
        void Trap();
        void Shot(int x, int y);
        bool CanTrap();
        bool CanShot();
};

class Barrel : public Entity{
    public:
        int rhum;
        Barrel();
        Barrel(int id, int x, int y, int rhum);
};

class Ball : public Entity{
    public:
        int idLanceur;
        int cooldown;
        Ball();
        Ball(int id, int x, int y, int idLanceur, int cooldown);
};

class Mine : public Entity{
    public:
        Mine();
        Mine(int id, int x, int y);
};

class Game{
    public:
        map <int, Ship> blue;
        map <int, Ship> red;
        map <int, Barrel> barrels;
        map <int, Ball> balls;
        map <int, Mine> mines;
        Game();
        void InputTurn();
        void Action();
    private:
        template <class entityType> void RefreshDico(map <int, entityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id);
};

Entity::Entity() : Entity(-1, 0, 0){}
Entity::Entity(int id, int x, int y){Entity::Update(id, x, y);}
void Entity::Update(int id, int x, int y){this->id = id; this->x = x; this->y = y;}
Ship::Ship() : Entity(){this->cooldownShot = 0; this->cooldownTrap = 0; this->idBarrelGoal = -1;}
void Ship::Update(int id, int x, int y, int cap, int vitesse, int rhum){Entity::Update(id, x, y);this->cap = cap; this->vitesse = vitesse; this->rhum = rhum; if(cooldownShot > 0){cooldownShot--;} if(cooldownTrap > 0){cooldownTrap--;}}
void Ship::Goto(int x, int y){cout << "MOVE " << x << " " << y << endl;}
void Ship::Shot(int x, int y){cout << "FIRE " << x << " " << y << endl; if(cooldownShot == 0){cooldownShot = CD_SHOT;}}
void Ship::Wait(){cout << "WAIT" << endl;}
void Ship::Slow(){cout << "SLOW" << endl;}
void Ship::Trap(){cout << "MINE" << endl; if(cooldownTrap == 0){cooldownTrap = CD_MINE;}}
bool Ship::CanTrap(){return cooldownTrap == 0;}
bool Ship::CanShot(){return cooldownShot == 0;}
Barrel::Barrel() : Entity(){}
Barrel::Barrel(int id, int x, int y, int rhum) : Entity(id, x, y){this->rhum = rhum;}
Ball::Ball() : Entity(){}
Ball::Ball(int id, int x, int y, int idLanceur, int cooldown) : Entity(id, x, y){this->idLanceur = idLanceur; this->cooldown = cooldown;}
Mine::Mine() : Entity(){}
Mine::Mine(int id, int x, int y) : Entity(id, x, y){}

Game::Game(){}

void Game::InputTurn(){
    map <int, bool> blueStillExists, redStillExists;
    barrels.clear();
    balls.clear();
    mines.clear();
    int nbShips, nbEntities;
    cin >> nbShips; cin.ignore();
    cin >> nbEntities; cin.ignore();
    for(int i = 0; i < nbEntities; i++){
        int id, x, y, arg1, arg2, arg3, arg4;
        string entityType;
        cin >> id >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
        switch(entityType[0]){
            case 'S':
                if(arg4){
                    RefreshDico<Ship>(&blue, &blueStillExists, id);
                    blue[id].Update(id, x, y, arg1, arg2, arg3);
                }
                else{
                    RefreshDico<Ship>(&red, &redStillExists, id);
                    red[id].Update(id, x, y, arg1, arg2, arg3);
                }
                break;
            case 'B':
                barrels[id] = Barrel(id, x, y, arg1);
                break;
            case 'C':
                balls[id] = Ball(id, x, y, arg1, arg2);
                break;
            case 'M':
                mines[id] = Mine(id, x, y);
                break;
            default:
                break;
        }
    }
    for(map <int, Ship> ::iterator it = blue.begin(); it != blue.end();){
        if(blueStillExists.find(it->first) == blueStillExists.end()){it = blue.erase(it);}
        else{++it;}
    }
    for(map <int, Ship> ::iterator it = red.begin(); it != red.end();){
        if(redStillExists.find(it->first) == redStillExists.end()){it = red.erase(it);}
        else{++it;}
    }
}

template <class entityType> void Game::RefreshDico(map <int, entityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id){
    if(dicoToRefresh->find(id) == dicoToRefresh->end()){(*dicoToRefresh)[id] = entityType();}
    (*dicoStillExists)[id] = true;
}

void Game::Action(){
    bool tirMobile = true;
    forMap(int, Ship, it, blue){
        Ship* myShip = &it->second;
        Ship* danger = NULL;
        Barrel* rhum = NULL;
        int distanceDanger = DIST_MAX;
        int distanceRhum = DIST_MAX;
        int xCible = -1;
        int yCible = -1;
        forMap(int, Ship, it2, red){
            Ship* enShip = &it2->second;
            int xCibleTest = enShip->x;
            int yCibleTest = enShip->y;
            int vitesse = enShip->vitesse * 2;
            switch(enShip->cap){
                case 0:
                    xCibleTest += vitesse;
                    break;
                case 1:
                    xCibleTest += (vitesse + enShip->x % 2) / 2;
                    yCibleTest -= vitesse;
                    break;
                case 2:
                    xCibleTest -= (vitesse + (enShip->x + 1) % 2) / 2;
                    yCibleTest -= vitesse;
                    break;
                case 3:
                    xCibleTest -= vitesse;
                    break;
                case 4:
                    xCibleTest -= (vitesse + (enShip->x + 1) % 2) / 2;
                    yCibleTest += vitesse;
                    break;
                case 5:
                    xCibleTest += (vitesse + enShip->x % 2) / 2;
                    yCibleTest += vitesse;
                    break;
                default:
                    break;
            }
            int distance = Utils::Distance(myShip->x, myShip->y, xCibleTest, yCibleTest);
            if(distance < distanceDanger && (enShip->vitesse == 0 || tirMobile)){
                distanceDanger = distance;
                danger = enShip;
                xCible = xCibleTest;
                yCible = yCibleTest;
            }
        }
        if(barrels.find(myShip->idBarrelGoal) == barrels.end()){
            forMap(int, Barrel, it2, barrels){
                Barrel* barrel = &it2->second;
                int distance = Utils::Distance(myShip->x, myShip->y, barrel->x, barrel->y);
                if(distance < distanceRhum){
                    distanceRhum = distance;
                    rhum = barrel;
                    myShip->idBarrelGoal = barrel->id;
                }
            }
        }
        else{
            rhum = &barrels[myShip->idBarrelGoal];
        }

        if(danger != NULL && distanceDanger < PORTEE_SHOT && myShip->CanShot() && (myShip->vitesse == 0 || tirMobile)){
            myShip->Shot(xCible, yCible);
        }
        else if(rhum != NULL){
            myShip->Goto(rhum->x, rhum->y);
        }
        else if(red.size() > 0){
            int xGoal = red.begin()->second.x;
            int yGoal = red.begin()->second.y;
            myShip->Goto(xGoal, yGoal);
        }
        else{
            myShip->Wait();
        }
    }
}

int main(){
    Game game;
    while(1){
        game.InputTurn();
        game.Action();
    }
}

int Utils::Distance(int x1, int y1, int x2, int y2){
    int a1 = x1 - (y1 - y1 % 2) / 2;
    int c1 = y1;
    int b1 = - a1 - c1;
    int a2 = x2 - (y2 - y2 % 2) / 2;
    int c2 = y2;
    int b2 = - a2 - c2;
    return (abs(a1 - a2) + abs(b1 - b2) + abs(c1 - c2)) / 2;
}
