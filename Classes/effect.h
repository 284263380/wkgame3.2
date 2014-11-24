#pragma once
#include "cocos2d.h"
USING_NS_CC;
class effectInstance : public cocos2d::Node
{
public:
    static effectInstance* create(char* name);
    bool  InitEffect(char* name);
    void playEffect(bool);
public:
    CCAnimation *animation;
    Sprite*      m_pSprite;
};

class effectPlist : public cocos2d::Node
{
public:
    static effectPlist* create(char* name);
};