#include "Entity.h"

Entity::Entity() : Entity_readonly(){}

Entity::Entity(int id, int x, int y) : Entity_readonly(id, x, y){

}

void Entity::Update(int id, int x, int y){
    Entity_readonly::Update(id, x, y);

}