#ifndef GAME_READONLY_H
#define GAME_READONLY_H

#include "../custom/entities/Ship.h"
#include "../custom/entities/Barrel.h"
#include "../custom/entities/Ball.h"
#include "../custom/entities/Mine.h"

class Game_readonly{
    public:
        map <int, Ship> ships;
        map <int, Barrel> barrels;
        map <int, Ball> balls;
        map <int, Mine> mines;
        Game_readonly();
        void InputTurn();
        void Action();
    private:
        template <class EntityType> void DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists);
        template <class EntityType> void RefreshDico(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists, int id);
};

#endif