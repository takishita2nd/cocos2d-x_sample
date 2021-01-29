//
// Created by ntaki on 2021/01/10.
//

#ifndef PROJ_ANDROID_QESTLISTMENU_H
#define PROJ_ANDROID_QESTLISTMENU_H

#include "cocos2d.h"
#include "GameStatusData/CommonParameter.h"
#include "UIParts/Common.h"

typedef struct _TextLabel {
    cocos2d::Label* label;
    cocos2d::Vec2 point;
} TextLabel;

typedef struct _QuestListMenu {
    Parts parts;
    TextLabel questName;
} QuestListMenu;

typedef struct _QuestList {
    Parts parts;
    QuestListMenu questListMenu[QUEST_NUM];
    float scaleRate;
    bool isShow;
} QuestList;

#endif //PROJ_ANDROID_QESTLISTMENU_H
