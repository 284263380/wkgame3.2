#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
//using namespace Widget;
#include "creature.h"


#include "effect.h"
#include "creature.h"

class sceneMain : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void touchButton(cocos2d::Object* obj,TouchEventType type);
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch* touch, Event *event);
    void onTouchEnded(Touch* touch, Event *event);
    CREATE_FUNC(sceneMain);
};

class sceneMap : public cocos2d::Layer
{
public:
    //static sceneMap* create();
    sceneMap(std::string map1,std::string map2,CCPoint cp);
    //virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch* touch, Event *event);
    void onTouchEnded(Touch* touch, Event *event);
public:
    Sprite*  m_pSpriteMap;
    Action*  m_mapMoveAction;
    creatureSprite* m_player;
};