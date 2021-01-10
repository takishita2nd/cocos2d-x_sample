//
// Created by ntaki on 2020/12/19.
//

#ifndef PROJ_ANDROID_CHARADETAILWINDOW_H
#define PROJ_ANDROID_CHARADETAILWINDOW_H

#include "cocos2d.h"
#include "GameStatusData/Character.h"
#include "UIParts/Common.h"
#include "UIParts/CharaWindow.h"

typedef struct _CharaDetailWindow {
    Parts parts;
    float scaleRate;
    ParameterLabel HPLabel;
    ParameterLabel MPLabel;
    ParameterLabel AttackLabel;
    ParameterLabel MagicLabel;
    ParameterLabel SpeedLabel;
    int showIndex;
} CharaDetailWindow;

#endif //PROJ_ANDROID_CHARADETAILWINDOW_H
