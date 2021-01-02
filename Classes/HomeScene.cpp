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
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    // ボタンの配置
    float buttonScale = visibleSize.height / (visibleSize.height / 4.0);
    float buttonBase = 0.0;

    homeButton.sprite = Sprite::create("btnHome.png");
    if(homeButton.sprite != nullptr)
    {
        homeButton.sprite->setAnchorPoint(Vec2(1.0,1.0));
        homeButton.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, visibleSize.height + origin.y);
        homeButton.sprite->setPosition(homeButton.point);
        homeButton.size = Size(homeButton.sprite->getContentSize().width * buttonScale, homeButton.sprite->getContentSize().height * buttonScale);
        homeButton.sprite->setScale(buttonScale);
        buttonBase = visibleSize.height - homeButton.size.height;
        this->addChild(homeButton.sprite, 1);
    }

    charaButton.sprite = Sprite::create("btnChara.png");
    if (charaButton.sprite != nullptr)
    {
        charaButton.sprite->setAnchorPoint(Vec2(1.0,1.0));
        charaButton.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, buttonBase + origin.y);
        charaButton.sprite->setPosition(charaButton.point);
        charaButton.size = Size(charaButton.sprite->getContentSize().width * buttonScale, charaButton.sprite->getContentSize().height * buttonScale);
        charaButton.sprite->setScale(buttonScale);
        buttonBase -= charaButton.size.height;
        this->addChild(charaButton.sprite, 1);
    }

    equipButton.sprite = Sprite::create("btnEquip.png");
    if (equipButton.sprite != nullptr)
    {
        equipButton.sprite->setAnchorPoint(Vec2(1.0,1.0));
        equipButton.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, buttonBase + origin.y);
        equipButton.sprite->setPosition(equipButton.point);
        equipButton.size = Size(equipButton.sprite->getContentSize().width * buttonScale, equipButton.sprite->getContentSize().height * buttonScale);
        equipButton.sprite->setScale(buttonScale);
        buttonBase -= equipButton.size.height;
        this->addChild(equipButton.sprite, 1);
    }

    questButton.sprite = Sprite::create("btnQuest.png");
    if (questButton.sprite != nullptr)
    {
        questButton.sprite->setAnchorPoint(Vec2(1.0,1.0));
        auto questButtonScale = buttonBase / questButton.sprite->getContentSize().height;
        questButton.point = Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x,
                                 buttonBase + origin.y);
        questButton.sprite->setPosition(questButton.point);
        questButton.size = Size(questButton.sprite->getContentSize().width * questButtonScale, questButton.sprite->getContentSize().height * questButtonScale);
        questButton.sprite->setScale(questButtonScale);
        this->addChild(questButton.sprite, 1);
    }

    // ステータスウィンドウの配置
    auto xpos = (visibleSize.width - sprite->getContentSize().width * scaleRate) / 2.0;

    auto chara = gameStatus.Charactors->begin();
    for(int i = 0; i < 4; i++) {
        window[i].sprite = cocos2d::Sprite::create("btn02_03_s_bl.png");
        if (window[i].sprite != nullptr)
        {
            auto scaleRate = (visibleSize.height / 4) / window[i].sprite->getContentSize().height;
            window[i].point = Vec2(xpos + origin.x,
                                   origin.y + window[i].sprite->getContentSize().height * scaleRate * i);
            window[i].size = Size(window[i].sprite->getContentSize().width * scaleRate,
                                  window[i].sprite->getContentSize().height * scaleRate);
            window[i].sprite->setAnchorPoint(Vec2(0,0));
            window[i].sprite->setScale(scaleRate);
            window[i].sprite->setPosition(window[i].point);
            this->addChild(window[i].sprite);

            window[i].HPLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            auto str = String();
            str.appendWithFormat("HP:%d/%d", chara.operator*()->Hp, chara.operator*()->MaxHp);
            window[i].HPLabel.label->setString(str.getCString());
            window[i].HPLabel.label->setAnchorPoint(Vec2(0.0, 1.0));
            window[i].HPLabel.point = Vec2(window[i].point.x + window[i].point.x / 10.0,
                                           window[i].point.y + window[i].size.height - window[i].size.height / 20.0);
            window[i].HPLabel.label->setPosition(window[i].HPLabel.point);
            this->addChild(window[i].HPLabel.label, 10);

            window[i].MPLabel.label = Label::createWithTTF("", "fonts/msgothic.ttc", 10);
            str = String();
            str.appendWithFormat("MP:%d/%d", chara.operator*()->Mp, chara.operator*()->MaxMp);
            window[i].MPLabel.label->setString(str.getCString());
            window[i].MPLabel.label->setAnchorPoint(Vec2(0.0, 1.0));
            window[i].MPLabel.point = Vec2(window[i].point.x + window[i].point.x / 10.0,
                    window[i].HPLabel.label->getPosition().y - window[i].HPLabel.label->getContentSize().height - window[i].size.height / 20.0);
            window[i].MPLabel.label->setPosition(window[i].MPLabel.point);
            this->addChild(window[i].MPLabel.label, 10);
        }
        chara++;
    }

    detailWindow.scaleRate = visibleSize.height / window[0].sprite->getContentSize().height;
    detailWindow.point = Vec2(xpos + origin.x + window[0].size.width, origin.y);
    detailWindow.isShow = false;
    detailWindow.showIndex = -1;

    return true;
}

bool HomeScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    log("touch(%f, %f)", touch->getLocation().x, touch->getLocation().y);

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

    anime->setPosition(touch->getLocation().x, touch->getLocation().y);
    anime->runAction(animate);

    if(detailWindow.isShow)
    {
        this->removeChild(detailWindow.sprite);
        this->removeChild(detailWindow.HPLabel.label);
        this->removeChild(detailWindow.MPLabel.label);
        this->removeChild(detailWindow.AttackLabel.label);
        this->removeChild(detailWindow.MagicLabel.label);
        this->removeChild(detailWindow.SpeedLabel.label);
    }

    for(int i = 0; i < 4; i++)
    {
        if(isTouch(touch->getLocation(), &window[i]))
        {
            detailWindow.isShow = true;
            if(detailWindow.showIndex == i)
            {
                detailWindow.showIndex = -1;
                break;
            }
            detailWindow.showIndex = i;
            detailWindow.sprite = Sprite::create("btn02_03_s_bl.png");
            detailWindow.sprite->setAnchorPoint(Vec2(0.0, 0.0));
            detailWindow.sprite->setPosition(detailWindow.point);
            detailWindow.size = Size(window[i].sprite->getContentSize().width * detailWindow.scaleRate,
                                     window[i].sprite->getContentSize().height * detailWindow.scaleRate);
            detailWindow.sprite->setScale(detailWindow.scaleRate);
            this->addChild(detailWindow.sprite, 1);

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
            detailWindow.HPLabel.point = Vec2(detailWindow.point.x + detailWindow.point.x / 10.0,
                                              detailWindow.point.y + detailWindow.size.height - detailWindow.size.height / 10.0);
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

    return true;
}

bool HomeScene::isTouch(cocos2d::Vec2 location, CharaWindow *charaWindow)
{
    if(location.x >= charaWindow->point.x && location.x <= charaWindow->point.x + charaWindow->size.width
        && location.y >= charaWindow->point.y && location.y <= charaWindow->point.y + charaWindow->size.height)
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
