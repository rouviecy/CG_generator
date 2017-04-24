#include "Barrel_readonly.h"

Barrel_readonly::Barrel_readonly() : Entity(){
}

void Barrel_readonly::Update(int id, int x, int y, int rhum){
    Entity::Update(id, x, y);
    this->rhum = rhum;
};