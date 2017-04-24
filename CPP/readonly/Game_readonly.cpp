#include "./Game_readonly.h"

Game_readonly::Game_readonly(){
}

void Game_readonly::InputTurn(){
    map <int, bool> shipsStillExists, barrelsStillExists, ballsStillExists, minesStillExists;
    int teamSize, nbEntities;
    cin >> teamSize >> nbEntities; cin.ignore();
    for(int i = 0; i < 4; i++){
        int id, x, y, arg1, arg2, arg3, arg4;
        string entityType;
        cin >> id >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
        if(false){}
        else if(entityType.compare("SHIP") == 0){
            ships[id].Update(id, x, y, arg1, arg2, arg3);
            RefreshDico<Ship>(&ships, &shipsStillExists, id);
        }
        else if(entityType.compare("BARREL") == 0){
            barrels[id].Update(id, x, y, arg1);
            RefreshDico<Barrel>(&barrels, &barrelsStillExists, id);
        }
        else if(entityType.compare("CANNONBALL") == 0){
            balls[id].Update(id, x, y, arg1, arg2);
            RefreshDico<Ball>(&balls, &ballsStillExists, id);
        }
        else if(entityType.compare("MINE") == 0){
            mines[id].Update(id, x, y);
            RefreshDico<Mine>(&mines, &minesStillExists, id);
        }
    }
    DeleteObsoleteEntities<Ship>(&ships, &shipsStillExists);
    DeleteObsoleteEntities<Barrel>(&barrels, &barrelsStillExists);
    DeleteObsoleteEntities<Ball>(&balls, &ballsStillExists);
    DeleteObsoleteEntities<Mine>(&mines, &minesStillExists);
}

void Game_readonly::Action(){
    // Inserer ici les operations utiles pour chaque tour
}

template <class EntityType> void Game_readonly::DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists){
    forMapTypename(int, EntityType, it, (*dicoToClean)){
        if(dicoStillExists->find(it->first) == dicoStillExists->end()){it = dicoToClean->erase(it);}
        else{++it;}
    }
}

template <class EntityType> void Game_readonly::RefreshDico(map <int, EntityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id){
    if(dicoToRefresh->find(id) == dicoToRefresh->end()){(*dicoToRefresh)[id] = EntityType();}
    (*dicoStillExists)[id] = true;
}