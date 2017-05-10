#ifndef GAME_H
#define GAME_H

#include "../readonly/Game_readonly.h"

class Game : public Game_readonly{
    public:
        Game();
        void InputTurn();
        void Action();
    private:
};

#endif