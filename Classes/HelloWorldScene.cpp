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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Hello World", "fonts/msgothic.ttc", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/msgothic.ttc'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 10);
    }

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
    listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    // ボタンの配置
    float buttonScale = visibleSize.height / (visibleSize.height / 4.0);
    float buttonBase = 0.0;
    auto homeButton = Sprite::create("btnHome.png");
    if (homeButton == nullptr)
    {
        problemLoading("'btnHome.png'");
    }
    else
    {
        homeButton->setPosition(Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x, visibleSize.height + origin.y));
        homeButton->setAnchorPoint(Vec2(1.0,1.0));
        homeButton->setScale(buttonScale);
        buttonBase = visibleSize.height - homeButton->getContentSize().height * buttonScale;
        this->addChild(homeButton, 1);
    }

    auto charaButton = Sprite::create("btnChara.png");
    if (charaButton == nullptr)
    {
        problemLoading("'btnChara.png'");
    }
    else
    {
        charaButton->setPosition(Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x,
                                      buttonBase + origin.y));
        charaButton->setAnchorPoint(Vec2(1.0,1.0));
        charaButton->setScale(buttonScale);
        buttonBase -= charaButton->getContentSize().height * buttonScale;
        this->addChild(charaButton, 1);
    }

    auto equipButton = Sprite::create("btnEquip.png");
    if (equipButton == nullptr)
    {
        problemLoading("'btnEquip.png'");
    }
    else
    {
        equipButton->setPosition(Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x,
                                      buttonBase + origin.y));
        equipButton->setAnchorPoint(Vec2(1.0,1.0));
        equipButton->setScale(buttonScale);
        buttonBase -= equipButton->getContentSize().height * buttonScale;
        this->addChild(equipButton, 1);
    }

    float questButtonScale;
    auto questButton = Sprite::create("btnQuest.png");
    if (questButton == nullptr)
    {
        problemLoading("'btnQuest.png'");
    }
    else
    {
        auto questButtonScale = buttonBase / questButton->getContentSize().height;
        questButton->setPosition(Vec2(sprite->getPosition().x + sprite->getContentSize().width * scaleRate / 2 + origin.x,
                                      buttonBase + origin.y));
        questButton->setAnchorPoint(Vec2(1.0,1.0));
        questButton->setScale(questButtonScale);

        this->addChild(questButton, 1);
    }

    // ステータスウィンドウの配置
    auto xpos = (visibleSize.width - sprite->getContentSize().width * scaleRate) / 2.0;
    float windowScale;
    auto charaStatusWindow1 = Sprite::create("btn02_03_s_bl.png");
    if (charaStatusWindow1 == nullptr)
    {
        problemLoading("'btn02_03_s_bl.png'");
    }
    else
    {
        charaStatusWindow1->setPosition(Vec2(xpos + origin.x,origin.y));
        charaStatusWindow1->setAnchorPoint(Vec2(0,0));
        windowScale = (visibleSize.height / 4) / charaStatusWindow1->getContentSize().height;
        charaStatusWindow1->setScale(windowScale);

        this->addChild(charaStatusWindow1, 1);
    }

    auto charaStatusWindow2 = Sprite::create("btn02_03_s_bl.png");
    if (charaStatusWindow2 == nullptr)
    {
        problemLoading("'btn02_03_s_bl.png'");
    }
    else
    {
        charaStatusWindow2->setPosition(Vec2(xpos + origin.x ,origin.y + charaStatusWindow1->getContentSize().height * windowScale));
        charaStatusWindow2->setAnchorPoint(Vec2(0,0));
        charaStatusWindow2->setScale(windowScale);

        this->addChild(charaStatusWindow2, 1);
    }

    auto charaStatusWindow3 = Sprite::create("btn02_03_s_bl.png");
    if (charaStatusWindow3 == nullptr)
    {
        problemLoading("'btn02_03_s_bl.png'");
    }
    else
    {
        charaStatusWindow3->setPosition(Vec2(xpos + origin.x ,origin.y + charaStatusWindow1->getContentSize().height * 2 * windowScale));
        charaStatusWindow3->setAnchorPoint(Vec2(0,0));
        charaStatusWindow3->setScale(windowScale);

        this->addChild(charaStatusWindow3, 1);
    }

    auto charaStatusWindow4 = Sprite::create("btn02_03_s_bl.png");
    if (charaStatusWindow4 == nullptr)
    {
        problemLoading("'btn02_03_s_bl.png'");
    }
    else
    {
        charaStatusWindow4->setPosition(Vec2(xpos + origin.x ,origin.y + charaStatusWindow1->getContentSize().height * 3 * windowScale));
        charaStatusWindow4->setAnchorPoint(Vec2(0,0));
        charaStatusWindow4->setScale(windowScale);

        this->addChild(charaStatusWindow4, 1);
    }

    auto str = String();
    str.appendWithFormat("windowScale %f", windowScale);
    label->setString(str.getCString());

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
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
    for(int i = 0; i < 15; i++) {
        animFrames.pushBack(SpriteFrame::create("pipo-btleffect007.png", Rect(frameWidth * i,0,frameHeight,frameWidth)));
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.02f);
    Animate* animate = Animate::create(animation);

    anime->setPosition(touch->getLocation().x, touch->getLocation().y);
    anime->runAction(animate);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
