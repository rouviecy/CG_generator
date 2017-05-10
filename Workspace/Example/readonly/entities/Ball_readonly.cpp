#include "Ball_readonly.h"

Ball_readonly::Ball_readonly() : Entity(){
}

void Ball_readonly::Update(int id, int x, int y, int idLanceur, int cooldown){
    Entity::Update(id, x, y);
    this->idLanceur = idLanceur;
    this->cooldown = cooldown;
};