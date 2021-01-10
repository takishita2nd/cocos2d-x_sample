//
// Created by ntaki on 2020/11/21.
//

#ifndef PROJ_ANDROID_GAMESTATUS_H
#define PROJ_ANDROID_GAMESTATUS_H

#include <list>
#include "cocos2d.h"
#include "Character.h"

typedef struct _GameStatus{
    std::list<Character*> *Charactors;
} GameStatus;

extern GameStatus gameStatus;
extern void createGameData();
extern void destroyDamadata();

#endif //PROJ_ANDROID_GAMESTATUS_H
