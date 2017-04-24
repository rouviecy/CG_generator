#ifndef ENTITY_H
#define ENTITY_H

#include "../readonly/Entity_readonly.h"

class Entity : public Entity_readonly{
    public:
        Entity();
        Entity(int id, int x, int y);
        void Update(int id, int x, int y);
    private:
};

#endif