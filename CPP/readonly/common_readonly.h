#ifndef COMMON_READONLY_H
#define COMMON_READONLY_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)
#define forMapTypename(type1, type2, it, carte) for(typename map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)

#define DIST_MAX 1000
#define CD_SHOT 2
#define CD_MINE 5
#define PORTEE_SHOT 10

class Game;
class Entity;
class Ship;
class Barrel;
class Ball;
class Mine;

#endif