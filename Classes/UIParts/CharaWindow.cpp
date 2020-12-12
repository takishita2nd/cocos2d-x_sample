//
// Created by ntaki on 2020/12/12.
//

#include "CharaWindow.h"

CharaWindow::CharaWindow()
{
    sprite = cocos2d::Sprite::create("btn02_03_s_bl.png");
    if (sprite != nullptr)
    {
        sprite->setAnchorPoint(cocos2d::Vec2(0,0));
        auto offset = sprite->getContentSize().width / 10.0;
        hpLabel = cocos2d::Label::createWithTTF("Hello World", "fonts/msgothic.ttc", 6);
        if(hpLabel != nullptr)
        {
            hpLabel->setAnchorPoint(cocos2d::Vec2(0, 1));
            hpLabel->setPosition(cocos2d::Vec2(0, sprite->getContentSize().height));
            sprite->addChild(hpLabel);
        }
        MpLabel = cocos2d::Label::createWithTTF("Hello World", "fonts/msgothic.ttc", 6);
        if(MpLabel != nullptr)
        {
            MpLabel->setAnchorPoint(cocos2d::Vec2(0, 1));
            MpLabel->setPosition(cocos2d::Vec2(0, sprite->getContentSize().height - 1 * hpLabel->getContentSize().height));
            sprite->addChild(MpLabel);
        }
    }
}

CharaWindow::~CharaWindow()
{
}

void CharaWindow::setPosition(cocos2d::Vec2 vector)
{
    if (sprite != nullptr)
    {
        point = vector;
        sprite->setPosition(point);
    }
}

void CharaWindow::setScale(float rate)
{
    if (sprite != nullptr)
    {
        sprite->setScale(rate);
        size = cocos2d::Size(sprite->getContentSize().width * rate, sprite->getContentSize().height * rate);
    }
}

void CharaWindow::show(cocos2d::Scene* scene)
{
    if (sprite != nullptr && scene != nullptr)
    {
        scene->addChild(sprite, 1);
    }
}

void CharaWindow::hide(cocos2d::Scene *scene)
{
    if (sprite != nullptr && scene != nullptr)
    {
        scene->removeChild(sprite, false);
    }
}

cocos2d::Vec2 CharaWindow::getPosition()
{
    return point;
}

cocos2d::Size CharaWindow::getSize()
{
    return size;
}

cocos2d::Size CharaWindow::getSpriteContentSize()
{
    if (sprite != nullptr)
    {
        return sprite->getContentSize();
    }
}

void CharaWindow::setParameter(Character* chara)
{
    auto hpStr = cocos2d::String();
    hpStr.appendWithFormat("HP : %d", chara->MaxHp);
    hpLabel->setString(hpStr.getCString());

    auto mpStr = cocos2d::String();
    mpStr.appendWithFormat("MP : %d", chara->MaxMp);
    MpLabel->setString(mpStr.getCString());
}

bool CharaWindow::isTouch(cocos2d::Vec2 vector)
{
    return false;
}