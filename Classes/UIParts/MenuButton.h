//
// Created by ntaki on 2021/01/02.
//

#ifndef PROJ_ANDROID_MENUBUTTON_H
#define PROJ_ANDROID_MENUBUTTON_H

#include "cocos2d.h"

typedef struct _MenuButton {
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 point;
    cocos2d::Size size;
} MenuButton;

#endif //PROJ_ANDROID_MENUBUTTON_H
