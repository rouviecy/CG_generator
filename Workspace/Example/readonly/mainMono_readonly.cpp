#include "../custom/Game.cpp"
#include "Game_readonly.cpp"
#include "../custom/Entity.cpp"
#include "Entity_readonly.cpp"
#include "../custom/entities/Ship.cpp"
#include "entities/Ship_readonly.cpp"
#include "../custom/entities/Barrel.cpp"
#include "entities/Barrel_readonly.cpp"
#include "../custom/entities/Ball.cpp"
#include "entities/Ball_readonly.cpp"
#include "../custom/entities/Mine.cpp"
#include "entities/Mine_readonly.cpp"

#include "../custom/Game.h"

int main(){
    Game game;
    while(1){
        game.InputTurn();
        game.Action();
    }
}