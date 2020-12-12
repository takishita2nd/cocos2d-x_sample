//
// Created by ntaki on 2020/12/12.
//

#ifndef PROJ_ANDROID_CHARAWINDOW_H
#define PROJ_ANDROID_CHARAWINDOW_H

#include "cocos2d.h"
#include "GameStatusData/Character.h"

class CharaWindow {
private:
    cocos2d::Vec2 point;
    cocos2d::Size size;
    cocos2d::Sprite* sprite;
    cocos2d::Label* hpLabel;
    cocos2d::Label* MpLabel;
public:
    CharaWindow();
    ~CharaWindow();

    void show(cocos2d::Scene* scene);
    void hide(cocos2d::Scene* scene);
    cocos2d::Size getSpriteContentSize();
    cocos2d::Vec2 getPosition();
    cocos2d::Size getSize();
    void setPosition(cocos2d::Vec2 vector);
    void setScale(float rate);
    void setParameter(Character* chara);
    bool isTouch(cocos2d::Vec2 vector);
};


#endif //PROJ_ANDROID_CHARAWINDOW_H
