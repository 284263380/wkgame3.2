#include "sceneMain.h"
#include "globalData.h"



Scene* sceneMain::createScene()
{
    auto scene = Scene::create();
    auto layer = sceneMain::create();
    scene->addChild(layer);
    return scene;
}
bool sceneMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    if(!g_globalData)
    {
        g_globalData = new globalData;
        g_globalData->Init();
    }

    //auto xx = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/login/DemoLogin.json");
    //addChild(xx);
    //ui::Button* buttonA = dynamic_cast<ui::Button*>(xx->getChildByName("login_Button"));
    //buttonA->addTouchEventListener(this,toucheventselector(sceneMain::touchButton));

//      {
//         effectInstance* effect = effectInstance::create("a008");
//         effect->setPosition(500,100);
//         addChild(effect);
//         effect->playEffect();
//      }
     //触摸
     auto listener = EventListenerTouchOneByOne::create();//创建一个触摸监听(单点触摸）
     listener->onTouchBegan = CC_CALLBACK_2(sceneMain::onTouchBegan, this);//指定触摸的回调函数
     listener->onTouchMoved = CC_CALLBACK_2(sceneMain::onTouchMoved, this);//指定触摸的回调函数
     listener->onTouchEnded = CC_CALLBACK_2(sceneMain::onTouchEnded, this);//指定触摸的回调函数
     _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将listener放入事件委托中

     sceneMap* _map = new sceneMap("map_diyu_naihe.jpg","map_diyu_naihe0.jpg",ccp(1,1));
     addChild(_map);
    return true;
}
void sceneMain::touchButton(cocos2d::Object* obj,TouchEventType type) 
{
    CCLOG("xxxx = %d\n",type);
}
bool sceneMain::onTouchBegan(Touch *touch, Event *event)
{
    //CCLOG("xxxx = %d\n",type);
    return true;
}
void sceneMain::onTouchMoved(Touch* touch, Event *event)
{

}
void sceneMain::onTouchEnded(Touch* touch, Event *event)
{

}
//////////////////////////////////////////////////////////////////////////
sceneMap::sceneMap(std::string map1,std::string map2,CCPoint cp)
{
    m_mapMoveAction = NULL;
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_pSpriteMap = Sprite::create(map1);
    addChild(m_pSpriteMap);
    float map_x , map_y;
    map_y = m_pSpriteMap->getAnchorPointInPoints().y+origin.y;
    map_x = m_pSpriteMap->getAnchorPointInPoints().x;
    m_pSpriteMap->setPosition(ccp(size.width/2-108,size.height/2-186));


    auto listener = EventListenerTouchOneByOne::create();//创建一个触摸监听(单点触摸）
    listener->onTouchBegan = CC_CALLBACK_2(sceneMap::onTouchBegan, this);//指定触摸的回调函数
    listener->onTouchMoved = CC_CALLBACK_2(sceneMap::onTouchMoved, this);//指定触摸的回调函数
    listener->onTouchEnded = CC_CALLBACK_2(sceneMap::onTouchEnded, this);//指定触摸的回调函数
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//将listener放入事件委托中
}
bool sceneMap::onTouchBegan(Touch *touch, Event *event)
{
    CCPoint cp = touch->getLocation();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize size2 = CCDirector::sharedDirector()->getVisibleSize();
    CCLog("(%f,%f)(%f,%f)(%f,%f)(%f,%f)\n",cp.x,cp.y,size.width,size.height,origin.x,origin.y,size2.width,size2.height);
    CCPoint cp2 = m_pSpriteMap->getPosition();

    float map_x = cp2.x+size.width/2-cp.x;
    float map_y = cp2.y+size.height/2-cp.y;
    //m_pSpriteMap->setPosition(map_x,map_y);d
    m_pSpriteMap->stopAction(m_mapMoveAction);
    m_mapMoveAction = CCMoveTo::create(2.0,ccp((int)map_x,(int)map_y));
    m_pSpriteMap->runAction(m_mapMoveAction);
    return true;
}
void sceneMap::onTouchMoved(Touch* touch, Event *event)
{

}
void sceneMap::onTouchEnded(Touch* touch, Event *event)
{

}