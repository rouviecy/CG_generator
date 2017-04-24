#ifndef BARREL_READONLY_H
#define BARREL_READONLY_H

#include "../../custom/Entity.h"

class Barrel_readonly : public Entity{
    public:
        int rhum;
        Barrel_readonly();
        void Update(int id, int x, int y, int rhum);
};

#endif