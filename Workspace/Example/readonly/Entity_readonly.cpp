#include "Entity_readonly.h"

Entity_readonly::Entity_readonly() : Entity_readonly(-1, 0, 0){}

Entity_readonly::Entity_readonly(int id, int x, int y){
    Entity_readonly::Update(id, x, y);
}

void Entity_readonly::Update(int id, int x, int y){
    this->id = id;
    this->x = x;
    this->y = y;
}