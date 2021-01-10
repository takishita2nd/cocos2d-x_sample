//
// Created by ntaki on 2020/12/12.
//

#ifndef PROJ_ANDROID_CHARAWINDOW_H
#define PROJ_ANDROID_CHARAWINDOW_H

#include "cocos2d.h"
#include "UIParts/Common.h"
#include "GameStatusData/Character.h"

typedef struct _ParameterLabel {
    cocos2d::Label* label;
    cocos2d::Vec2 point;
} ParameterLabel;

typedef struct _CharaWindow {
    Parts parts;
    ParameterLabel HPLabel;
    ParameterLabel MPLabel;
} CharaWindow;



#endif //PROJ_ANDROID_CHARAWINDOW_H
