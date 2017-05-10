#ifndef BALL_READONLY_H
#define BALL_READONLY_H

#include "../../custom/Entity.h"

class Ball_readonly : public Entity{
    public:
        int idLanceur;
        int cooldown;
        Ball_readonly();
        void Update(int id, int x, int y, int idLanceur, int cooldown);
};

#endif