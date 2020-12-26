//
// Created by ntaki on 2020/11/28.
//

#ifndef PROJ_ANDROID_CHARACTER_H
#define PROJ_ANDROID_CHARACTER_H

#include "cocos2d.h"

typedef struct Character {
    int Hp;
    int MaxHp;
    int Mp;
    int MaxMp;
    int Power;
    int Speed;
    int Magic;
} Character;

extern Character* createCharactor();

#endif //PROJ_ANDROID_CHARACTER_H
