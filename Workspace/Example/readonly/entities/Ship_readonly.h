#ifndef SHIP_READONLY_H
#define SHIP_READONLY_H

#include "../../custom/Entity.h"

class Ship_readonly : public Entity{
    public:
        int cap;
        int vitesse;
        int rhum;
        int cooldownShot;
        int cooldownTrap;
        int idBarrelGoal;
        Ship_readonly();
        void Update(int id, int x, int y, int cap, int vitesse, int rhum);
};

#endif