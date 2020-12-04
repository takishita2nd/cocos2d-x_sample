//
// Created by ntaki on 2020/11/21.
//

#ifndef PROJ_ANDROID_GAMESTATUS_H
#define PROJ_ANDROID_GAMESTATUS_H

#include "cocos2d.h"
#include "Character.h"
#include <list>

class GameStatus {
private:
    static GameStatus *gameStatus;
public:
    std::list<Character*> *Charactors;
private:
    GameStatus();
    ~GameStatus();
public:
    static GameStatus* GetGameData();
    static void Destroy();
};


#endif //PROJ_ANDROID_GAMESTATUS_H
