#include "effect.h"
#include "globalData.h"


effectInstance* effectInstance::create(char* name)
{
    effectInstance* effect = new effectInstance;
    if(!effect->InitEffect(name))
    {
        effect->release();
        return NULL;
    }
    effect->autorelease();
    return effect;
}
bool effectInstance::InitEffect(char* name)
{
    EffectClass* effClass = g_globalData->resFindEffect(name);
    if(!effClass)
        return false;
    if(effClass->type == 1)
    {
        char sz[128] = {0};
        sprintf(sz, effClass->file, effClass->effStart);
        m_pSprite = Sprite::create(sz);
        addChild(m_pSprite);
        animation = CCAnimation::create();
        for(int i=effClass->effStart;i<effClass->effStart+effClass->effCnt;i++)
        {
            char szImageFileName[128] = {0};  
            sprintf(szImageFileName, effClass->file, i);  
            animation->addSpriteFrameWithFileName(szImageFileName);
        }
        animation->setLoops(effClass->loopCnt);
        animation->setDelayPerUnit(effClass->effectDelay/effClass->effCnt);
        animation->setRestoreOriginalFrame(effClass->IsRestoreOrg);
    }
    else if(effClass->type == 2)
    {  
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(effClass->plistPath);
        char sz[128] = {0};
        sprintf(sz, effClass->file, effClass->effStart);
        m_pSprite = Sprite::createWithSpriteFrameName(sz);
        //m_pSprite = Sprite::create();
        addChild(m_pSprite);
        CCArray*frames=CCArray::create();
        Vector<SpriteFrame*> vecsf;
        for(int i=effClass->effStart;i<effClass->effStart+effClass->effCnt;i++)
        {
            char szImageFileName[128] = {0};  
            sprintf(szImageFileName, effClass->file, i);
            SpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName(szImageFileName);
            vecsf.pushBack(sf);
        }
        animation = CCAnimation::createWithSpriteFrames(vecsf,effClass->effectDelay/effClass->effCnt);
        animation->setDelayPerUnit(effClass->effectDelay/effClass->effCnt);
        animation->setLoops(effClass->loopCnt);
        animation->setRestoreOriginalFrame(effClass->IsRestoreOrg);
    }
    return true;
}
void effectInstance::playEffect()
{
    CCAnimate *action = CCAnimate::create(animation);
    m_pSprite->runAction(action);  // 运行精灵对象  
}