#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;

class creatureData
{
public:
    creatureData();
    ~creatureData();
    int m_speedMove;
    int m_speedAttack;
};


class creatureSprite : public Sprite
{
public:
    creatureSprite();
    ~creatureSprite();
    void poseAttack();
    void poseRun();
    void poseWalk();
    void poseBeAttacked();
public:
    Sprite*       m_pShadow;//ÒõÓ°
    creatureData* m_pData;  //Êý¾Ý
};