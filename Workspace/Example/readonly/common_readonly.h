#ifndef COMMON_READONLY_H
#define COMMON_READONLY_H

#ifndef EXPLICITE_EXCLUDE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#endif

using namespace std;

#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)
#define forMapTypename(type1, type2, it, carte) for(typename map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)

#define PORTEE_SHOT 10
#define CD_SHOT 2
#define CD_MINE 5
#define DIST_MAX 1000

class Game;
class Entity;
class Ship;
class Barrel;
class Ball;
class Mine;

#endif