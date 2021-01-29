/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HomeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HomeScene::createScene()
{
    return HomeScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Label* label;
// on "init" you need to initialize your instance
bool HomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    detailWindow.parts.isShow = false;
    questListMenu.parts.isShow = false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("ID003_Western-Castle_noon.jpg");
    if (sprite == nullptr)
    {
        problemLoading("'ID003_Western-Castle_noon.jpg'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprite, 0);
    }
    auto scaleRate = visibleSize.height / sprite->getContentSize().height;
    sprite->setScale(scaleRate);

    // タッチアニメーション
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    // ボタンの配置
    float buttonScale = visibleSize.height / (visibleSize.height / 4.0);
    float buttonBase = 0.0;

    homeButton.parts.sprite = Sprite::create("btnHome.png");
    if(homeButton.parts.sprite != nullptr)
    {
        homeButton.parts.sprite->setAnchorPoint(Vec2(1.0,1.0));
        homeButton.parts.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, visibleSize.height + origin.y);
        homeButton.parts.sprite->setPosition(homeButton.parts.point);
        homeButton.parts.size = Size(homeButton.parts.sprite->getContentSize().width * buttonScale, homeButton.parts.sprite->getContentSize().height * buttonScale);
        homeButton.parts.sprite->setScale(buttonScale);
        buttonBase = visibleSize.height - homeButton.parts.size.height;
        this->addChild(homeButton.parts.sprite, 1);
    }

    charaButton.parts.sprite = Sprite::create("btnChara.png");
    if (charaButton.parts.sprite != nullptr)
    {
        charaButton.parts.sprite->setAnchorPoint(Vec2(1.0,1.0));
        charaButton.parts.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, buttonBase + origin.y);
        charaButton.parts.sprite->setPosition(charaButton.parts.point);
        charaButton.parts.size = Size(charaButton.parts.sprite->getContentSize().width * buttonScale, charaButton.parts.sprite->getContentSize().height * buttonScale);
        charaButton.parts.sprite->setScale(buttonScale);
        buttonBase -= charaButton.parts.size.height;
        this->addChild(charaButton.parts.sprite, 1);
    }

    equipButton.parts.sprite = Sprite::create("btnEquip.png");
    if (equipButton.parts.sprite != nullptr)
    {
        equipButton.parts.sprite->setAnchorPoint(Vec2(1.0,1.0));
        equipButton.parts.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, buttonBase + origin.y);
        equipButton.parts.sprite->setPosition(equipButton.parts.point);
        equipButton.parts.size = Size(equipButton.parts.sprite->getContentSize().width * buttonScale, equipButton.parts.sprite->getContentSize().height * buttonScale);
        equipButton.parts.sprite->setScale(buttonScale);
        buttonBase -= equipButton.parts.size.height;
        this->addChild(equipButton.parts.sprite, 1);
    }

    questButton.parts.sprite = Sprite::create("btnQuest.png");
    if (questButton.parts.sprite != nullptr)
    {
        questButton.parts.sprite->setAnchorPoint(Vec2(1.0,1.0));
        auto questButtonScale = buttonBase / questButton.parts.sprite->getContentSize().height;
        questButton.parts.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x,
                                 buttonBase + origin.y);
        questButton.parts.sprite->setPosition(questButton.parts.point);
        questButton.parts.size = Size(questButton.parts.sprite->getContentSize().width * questButtonScale, questButton.parts.sprite->getContentSize().height * questButtonScale);
        questButton.parts.point = Vec2(questButton.parts.point.x - questButton.parts.size.width,
                                       questButton.parts.point.y - questButton.parts.size.height);
        questButton.parts.sprite->setScale(questButtonScale);
        this->addChild(questButton.parts.sprite, 1);
    }

    // ステータスウィンドウの配置
    auto xpos = (visibleSize.width - sprite->getContentSize().width * scaleRate) / 2.0;

    auto chara = gameStatus.Charactors->begin();
    for(int i = 0; i < 4; i++) {
        window[i].parts.sprite = cocos2d::Sprite::create("btn02_03_s_bl.png");
        if (window[i].parts.sprite != nullptr)
        {
            auto scaleRate = (visibleSize.height / 4) / window[i].parts.sprite->getContentSize().height;
            window[i].parts.point = Vec2(xpos + origin.x,
                                   origin.y + window[i].parts.sprite->getContentSize().height * scaleRate * i);
            window[i].parts.size = Size(window[i].parts.sprite->getContentSize().width * scaleRate,
                                  window[i].parts.sprite->getContentSize().height * scaleRate);
            window[i].parts.sprite->setAnchorPoint(Vec2(0,0));
            window[i].parts.sprite->setScale(scaleRate);
            window[i].parts.sprite->setPosition(window[i].parts.point);
            this->addChild(window[i].parts.sprite);

            window[i].HPLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            auto str = String();
            str.appendWithFormat("HP:%d/%d", chara.operator*()->Hp, chara.operator*()->MaxHp);
            window[i].HPLabel.label->setString(str.getCString());
            window[i].HPLabel.label->setAnchorPoint(Vec2(0.0, 1.0));
            window[i].HPLabel.point = Vec2(window[i].parts.point.x + window[i].parts.point.x / 10.0,
                                           window[i].parts.point.y + window[i].parts.size.height - window[i].parts.size.height / 20.0);
            window[i].HPLabel.label->setPosition(window[i].HPLabel.point);
            this->addChild(window[i].HPLabel.label, 10);

            window[i].MPLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            str = String();
            str.appendWithFormat("MP:%d/%d", chara.operator*()->Mp, chara.operator*()->MaxMp);
            window[i].MPLabel.label->setString(str.getCString());
            window[i].MPLabel.label->setAnchorPoint(Vec2(0.0, 1.0));
            window[i].MPLabel.point = Vec2(window[i].parts.point.x + window[i].parts.point.x / 10.0,
                    window[i].HPLabel.label->getPosition().y - window[i].HPLabel.label->getContentSize().height - window[i].parts.size.height / 20.0);
            window[i].MPLabel.label->setPosition(window[i].MPLabel.point);
            this->addChild(window[i].MPLabel.label, 10);
        }
        chara++;
    }

    detailWindow.scaleRate = visibleSize.height / window[0].parts.sprite->getContentSize().height;
    questListMenu.scaleRate = detailWindow.scaleRate;
    detailWindow.parts.point = Vec2(xpos + origin.x + window[0].parts.size.width, visibleSize.height + origin.y);
    questListMenu.parts.point = detailWindow.parts.point;
    detailWindow.parts.isShow = false;
    detailWindow.showIndex = -1;

    return true;
}

bool HomeScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    log("touch(%f, %f)", touch->getLocation().x, touch->getLocation().y);

    actionTouchAnime(touch->getLocation());

    if(detailWindow.parts.isShow)
    {
        this->removeChild(detailWindow.parts.sprite);
        this->removeChild(detailWindow.HPLabel.label);
        this->removeChild(detailWindow.MPLabel.label);
        this->removeChild(detailWindow.AttackLabel.label);
        this->removeChild(detailWindow.MagicLabel.label);
        this->removeChild(detailWindow.SpeedLabel.label);
    }

    for(int i = 0; i < 4; i++)
    {
        if(isTouch(touch->getLocation(), &(window[i].parts)))
        {
            detailWindow.parts.isShow = true;
            if(detailWindow.showIndex == i)
            {
                detailWindow.showIndex = -1;
                break;
            }
            detailWindow.showIndex = i;
            detailWindow.parts.sprite = Sprite::create("btn02_03_s_bl.png");
            detailWindow.parts.sprite->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.parts.sprite->setPosition(detailWindow.parts.point);
            detailWindow.parts.size = Size(detailWindow.parts.sprite->getContentSize().width * detailWindow.scaleRate,
                                           detailWindow.parts.sprite->getContentSize().height * detailWindow.scaleRate);
            detailWindow.parts.sprite->setScale(detailWindow.scaleRate);
            this->addChild(detailWindow.parts.sprite, 1);

            auto character = gameStatus.Charactors->begin();
            for(int j = 0; j < i; j++)
            {
                character++;
            }
            detailWindow.HPLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            auto str = String();
            str.appendWithFormat("HP:%d/%d", character.operator*()->Hp, character.operator*()->MaxHp);
            detailWindow.HPLabel.label->setString(str.getCString());
            detailWindow.HPLabel.label->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.HPLabel.point = Vec2(detailWindow.parts.point.x + detailWindow.parts.point.x / 10.0,
                                              detailWindow.parts.point.y + detailWindow.parts.size.height - detailWindow.parts.size.height / 10.0);
            detailWindow.HPLabel.label->setPosition(detailWindow.HPLabel.point);
            this->addChild(detailWindow.HPLabel.label, 10);

            detailWindow.MPLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            str = String();
            str.appendWithFormat("MP:%d/%d", character.operator*()->Mp, character.operator*()->MaxMp);
            detailWindow.MPLabel.label->setString(str.getCString());
            detailWindow.MPLabel.label->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.MPLabel.point = Vec2(detailWindow.HPLabel.point.x,
                                              detailWindow.HPLabel.point.y - detailWindow.HPLabel.label->getContentSize().height);
            detailWindow.MPLabel.label->setPosition(detailWindow.MPLabel.point);
            this->addChild(detailWindow.MPLabel.label, 10);

            detailWindow.AttackLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            str = String();
            str.appendWithFormat("攻撃力:%d", character.operator*()->Power);
            detailWindow.AttackLabel.label->setString(str.getCString());
            detailWindow.AttackLabel.label->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.AttackLabel.point = Vec2(detailWindow.HPLabel.point.x,
                                              detailWindow.MPLabel.point.y - detailWindow.MPLabel.label->getContentSize().height);
            detailWindow.AttackLabel.label->setPosition(detailWindow.AttackLabel.point);
            this->addChild(detailWindow.AttackLabel.label, 10);

            detailWindow.MagicLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            str = String();
            str.appendWithFormat("魔力:%d", character.operator*()->Magic);
            detailWindow.MagicLabel.label->setString(str.getCString());
            detailWindow.MagicLabel.label->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.MagicLabel.point = Vec2(detailWindow.HPLabel.point.x,
                                                  detailWindow.AttackLabel.point.y - detailWindow.AttackLabel.label->getContentSize().height);
            detailWindow.MagicLabel.label->setPosition(detailWindow.MagicLabel.point);
            this->addChild(detailWindow.MagicLabel.label, 10);

            detailWindow.SpeedLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            str = String();
            str.appendWithFormat("スピード:%d", character.operator*()->Speed);
            detailWindow.SpeedLabel.label->setString(str.getCString());
            detailWindow.SpeedLabel.label->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.SpeedLabel.point = Vec2(detailWindow.HPLabel.point.x,
                                                 detailWindow.MagicLabel.point.y - detailWindow.MagicLabel.label->getContentSize().height);
            detailWindow.SpeedLabel.label->setPosition(detailWindow.SpeedLabel.point);
            this->addChild(detailWindow.SpeedLabel.label, 10);
        }
    }

    if(isTouch(touch->getLocation(), &(questButton.parts)))
    {
        questButton.touched = true;
    }

    if(questListMenu.isShow)
    {
        keepPosition = touch->getLocation();
    }

    return true;
}

void HomeScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    log("move(%f, %f)", touch->getLocation().x, touch->getLocation().y);

    if(questListMenu.isShow)
    {
        // Yの差分だけメニューを動かす
        float divY = touch->getLocation().y - keepPosition.y;
        for(int i = 0; i < QUEST_NUM; i++)
        {
            questListMenu.questListMenu[i].parts.sprite->setPosition(questListMenu.questListMenu[i].parts.point.x, questListMenu.questListMenu[i].parts.point.y + divY);
            questListMenu.questListMenu[i].parts.point.y = questListMenu.questListMenu[i].parts.point.y + divY;
            questListMenu.questListMenu[i].questName.label->setPosition(questListMenu.questListMenu[i].questName.point.x, questListMenu.questListMenu[i].questName.point.y + divY);
            questListMenu.questListMenu[i].questName.point.y = questListMenu.questListMenu[i].questName.point.y + divY;
        }
        keepPosition.y += divY;
    }
}

void HomeScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    log("release(%f, %f)", touch->getLocation().x, touch->getLocation().y);

    if(questButton.touched)
    {
        if(isTouch(touch->getLocation(), &(questButton.parts)))
        {
            auto questList = getQuestList();
            auto questName = questList->begin();
            for(int i = 0; i < questList->size(); i++)
            {
                log("loop");
                questListMenu.questListMenu[i].parts.sprite = Sprite::create("btn02_03_s_bl.png");
                questListMenu.questListMenu[i].parts.sprite->setAnchorPoint(Vec2(0.0, 0.0));
                questListMenu.questListMenu[i].parts.size = Size(questListMenu.questListMenu->parts.sprite->getContentSize().width * questListMenu.scaleRate,
                                                                 questListMenu.questListMenu->parts.sprite->getContentSize().height);
                questListMenu.questListMenu[i].parts.point = Vec2(questListMenu.parts.point.x, questListMenu.parts.point.y - questListMenu.questListMenu->parts.sprite->getContentSize().height * (i + 1));
                questListMenu.questListMenu[i].parts.sprite->setPosition(questListMenu.questListMenu[i].parts.point);
                questListMenu.questListMenu[i].parts.sprite->setScale(questListMenu.scaleRate, 1);
                this->addChild(questListMenu.questListMenu[i].parts.sprite, 5);

                questListMenu.questListMenu[i].questName.label = Label::createWithTTF("", "fonts/msgothic.ttc", 18);
                auto str = String();
                str.appendWithFormat("%s", questName.operator*());
                questListMenu.questListMenu[i].questName.label->setString(str.getCString());
                questListMenu.questListMenu[i].questName.label->setAnchorPoint(Vec2(0.0, -0.3));
                questListMenu.questListMenu[i].questName.point = Vec2(questListMenu.questListMenu[i].parts.point.x + questListMenu.questListMenu[i].parts.size.width / 30.0, questListMenu.questListMenu[i].parts.point.y);
                questListMenu.questListMenu[i].questName.label->setPosition(questListMenu.questListMenu[i].questName.point);
                this->addChild(questListMenu.questListMenu[i].questName.label, 6);

                questName++;
            }
        }
        questButton.touched = false;
        questListMenu.isShow = true;
    }
}

void HomeScene::actionTouchAnime(cocos2d::Vec2 location)
{
    auto anime = Sprite::create("pipo-btleffect007.png");
    if (anime == nullptr)
    {
        problemLoading("'pipo-btleffect007.png'");
    }
    else
    {
        this->addChild(anime, 255);
    }
    float frameHeight = anime->getContentSize().height;
    float frameWidth = anime->getContentSize().width / 15.0;
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(15);
    for(int i = 0; i < 15; i++)
    {
        animFrames.pushBack(SpriteFrame::create("pipo-btleffect007.png", Rect(frameWidth * i,0,frameHeight,frameWidth)));
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.02f);
    Animate* animate = Animate::create(animation);

    anime->setPosition(location.x, location.y);
    anime->runAction(animate);
}

bool HomeScene::isTouch(cocos2d::Vec2 location, Parts *parts)
{
    if(location.x >= parts->point.x && location.x <= parts->point.x + parts->size.width
        && location.y >= parts->point.y && location.y <= parts->point.y + parts->size.height)
    {
        return true;
    }
    return false;
}

void HomeScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
