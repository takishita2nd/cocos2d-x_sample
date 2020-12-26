//
// Created by ntaki on 2020/11/28.
//

#include "Character.h"

Character* createCharactor()
{
    Character* character = (Character*)malloc(sizeof(Character));
    character->MaxHp = cocos2d::random<int>(0, 100);
    character->Hp = character->MaxHp;
    character->MaxMp = cocos2d::random<int>(0, 100);
    character->Mp = character->MaxMp;
    character->Power = cocos2d::random<int>(0, 100);
    character->Speed = cocos2d::random<int>(0, 100);
    character->Magic = cocos2d::random<int>(0, 100);
    return character;
}
