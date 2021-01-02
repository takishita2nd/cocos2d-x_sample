//
// Created by ntaki on 2020/12/19.
//

#ifndef PROJ_ANDROID_CHARADETAILWINDOW_H
#define PROJ_ANDROID_CHARADETAILWINDOW_H

#include "cocos2d.h"
#include "GameStatusData/Character.h"
#include "UIParts/CharaWindow.h"

typedef struct _CharaDetailWindow {
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 point;
    cocos2d::Size size;
    float scaleRate;
    ParameterLabel HPLabel;
    ParameterLabel MPLabel;
    ParameterLabel AttackLabel;
    ParameterLabel MagicLabel;
    ParameterLabel SpeedLabel;
    bool isShow;
    int showIndex;
} CharaDetailWindow;

#endif //PROJ_ANDROID_CHARADETAILWINDOW_H
