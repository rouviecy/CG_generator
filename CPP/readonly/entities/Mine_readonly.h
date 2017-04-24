#ifndef MINE_READONLY_H
#define MINE_READONLY_H

#include "../../custom/Entity.h"

class Mine_readonly : public Entity{
    public:
        Mine_readonly();
        void Update(int id, int x, int y);
};

#endif