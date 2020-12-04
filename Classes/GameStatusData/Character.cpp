//
// Created by ntaki on 2020/11/28.
//

#include "Character.h"

Character::Character()
{
    MaxHp = cocos2d::random<int>(0, 100);
    MaxMp = cocos2d::random<int>(0, 100);
    Power = cocos2d::random<int>(0, 100);
    Speed = cocos2d::random<int>(0, 100);
    Magic = cocos2d::random<int>(0, 100);
}

Character::~Character()
{

}