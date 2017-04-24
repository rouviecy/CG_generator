#include "../custom/Game.h"

int main(){
    Game game;
    while(1){
        game.InputTurn();
        game.Action();
    }
}