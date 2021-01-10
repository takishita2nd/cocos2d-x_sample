//
// Created by ntaki on 2021/01/10.
//

#ifndef PROJ_ANDROID_COMMON_H
#define PROJ_ANDROID_COMMON_H

#include "cocos2d.h"

typedef struct _PartsCommon {
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 point;
    cocos2d::Size size;
    bool isShow;
} Parts;

#endif //PROJ_ANDROID_COMMON_H
