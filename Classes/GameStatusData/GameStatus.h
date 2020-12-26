//
// Created by ntaki on 2020/11/21.
//

#ifndef PROJ_ANDROID_GAMESTATUS_H
#define PROJ_ANDROID_GAMESTATUS_H

#include "cocos2d.h"
#include "Character.h"
#include <list>

typedef struct GameStatus{
    std::list<Character*> *Charactors;
} GameStatus;

extern GameStatus gameStatus;
extern void createGameData();
extern void destroyDamadata();

#endif //PROJ_ANDROID_GAMESTATUS_H
