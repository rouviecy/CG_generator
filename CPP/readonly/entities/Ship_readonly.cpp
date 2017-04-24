#include "Ship_readonly.h"

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