#ifndef ENTITY_READONLY_H
#define ENTITY_READONLY_H

#include "../custom/common.h"

class Entity_readonly{
    public:
        int id;
        int x;
        int y;
        Entity_readonly();
        Entity_readonly(int id, int x, int y);
        void Update(int id, int x, int y);
};

#endif