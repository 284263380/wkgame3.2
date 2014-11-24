#include "wkUIBase.h"

USING_NC_UI
//////////////////////////////////////////////////////////////////////////
wkWidgetSlot* wkWidgetSlot::create()
{
    wkWidgetSlot *pRet = new wkWidgetSlot();
    if( pRet && pRet->init() )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
wkWidgetSlot::wkWidgetSlot()
{
    m_pSelectWidget = NULL;
    stateWidget = esw_init;
}
wkWidgetSlot::~wkWidgetSlot()
{

}
bool wkWidgetSlot::init()
{
    if(!CCNode::init())
        return false;
    setContentSize(CCDirector::sharedDirector()->getWinSize());
    ignoreAnchorPointForPosition(true);
    setAnchorPoint(CCPointZero);
    setPosition(CCPointZero);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    return true;
}
bool wkWidgetSlot::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(!isVisible())
        return false;
    CCPoint touchPointInView = convertToNodeSpace(pTouch->getLocation());
    if(!m_pChildren)
        return false;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH_REVERSE( m_pChildren, pObject )
    {
        wkWidget* pWidget = dynamic_cast<wkWidget*>(pObject);
        if(!pWidget)
            continue;
        if(!pWidget->isVisible())
            continue;
        if(pWidget->boundingBox().containsPoint(touchPointInView))
        {
            if(!pWidget->isEnable())
                break;
            if(!pWidget->getTouchEnable())
                break;
            m_pSelectWidget = pWidget;
            m_pSelectWidget->ccTouchBegan(pTouch,pEvent);
            stateWidget = esw_select;
            break;
        }
    }
    return true;
}
void wkWidgetSlot::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pSelectWidget)
    {
        m_pSelectWidget->ccTouchMoved(pTouch,pEvent);
        CCPoint touchPointInView = convertToNodeSpace(pTouch->getLocation());
        if(m_pSelectWidget->boundingBox().containsPoint(touchPointInView))
        {
            if(stateWidget== esw_unselect)
            {
                m_pSelectWidget->ccTouchSelect(pTouch,pEvent);
                stateWidget = esw_select;
            }
        }
        else
        {
            if(stateWidget == esw_select)
            {
                m_pSelectWidget->ccTouchUnSelect(pTouch,pEvent);
                stateWidget = esw_unselect;
            }
        }
    }
}
void wkWidgetSlot::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pSelectWidget)
    {
        m_pSelectWidget->ccTouchEnded(pTouch,pEvent);
        m_pSelectWidget = NULL;
        stateWidget = esw_init;
    }
}
void wkWidgetSlot::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if(m_pSelectWidget)
    {
        m_pSelectWidget->ccTouchCancelled(pTouch,pEvent);
        m_pSelectWidget = NULL;
        stateWidget = esw_init;
    }
}
void wkWidgetSlot::visit()
{
    CCNode::visit();
}
//////////////////////////////////////////////////////////////////////////
wkWidget *wkWidget::create(void)
{
    wkWidget* ret = new wkWidget;
    if(ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}
wkWidget::wkWidget()
{
    m_name = "";
    m_bIsTouchEnabled = true;
    m_bEnable = true;
    m_background = NULL;
}
wkWidget::~wkWidget()
{

}
bool wkWidget::init()
{
    setContentSize(CCDirector::sharedDirector()->getWinSize());
    return true;
}
bool wkWidget::init(CCSize cc)
{
    setContentSize(cc);
    return true;
}
void wkWidget::setTouchEnable(bool enable)
{
    if( m_bIsTouchEnabled != enable )
        m_bIsTouchEnabled = enable;
}
void wkWidget::setEnable(bool v)
{
    if(m_bEnable!=v)
    {
        m_bEnable = v;
        onEnableOnChange(v);
    }
}
bool wkWidget::isEnable()
{
    return m_bEnable;
}
void wkWidget::setBackground(const char* path,CCRect rect)
{
    m_background = new CCSprite;
    if(rect.equals(CCRectZero))
        m_background->initWithFile(path);
    else
        m_background->initWithFile(path,rect);
    addChild(m_background);
}
void wkWidget::visit()
{
    if(m_background)
    {
        CCSize size1 = getContentSize();
        CCSize size2 = m_background->getContentSize();
        m_background->setScaleX(size1.width/size2.width);
        m_background->setScaleY(size1.height/size2.height);
        m_background->setPosition(ccp(size1.width/2,size1.height/2));
    }
    {

    }
    CCNode::visit();
}
void wkWidget::setText(string& text)
{
    m_text = text;
}
string wkWidget::getText()
{
    return m_text;
}
//////////////////////////////////////////////////////////////////////////
wkButton *wkButton::create()
{
    wkButton* ret = new wkButton;
    if(ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}
wkButton *wkButton::create(const char* normalImg,const char* selectImg,const char* disableImg)
{
    wkButton* ret = new wkButton;
    if(ret && ret->initWidthFile(normalImg,selectImg,disableImg))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}
wkButton::wkButton()
{
    m_pNormalImage = NULL;
    m_pSelectedImage = NULL;
    m_pDisabledImage = NULL;
    setTouchEnable(true);
    m_state = 0;
}
wkButton::~wkButton()
{
    setColor(ccc3(255,0,0));
}
bool wkButton::init()
{
    setTouchEnable(true);
    return true;
}
bool wkButton::initWidthFile(const char* normalImg,const char* selectImg,const char* disableImg)
{
    setNormalImage(normalImg);
    setSelectedImage(selectImg);
    setDisabledImage(disableImg);
    m_pNormalImage->setVisible(true);
    m_pSelectedImage->setVisible(false);
    m_pDisabledImage->setVisible(false);
    CCSize size = m_pNormalImage->getContentSize();
    setContentSize(size);
    return true;
}
void wkButton::setNormalImage(const char* pFile,CCRect rect)
{
     m_pNormalImage = new CCSprite;
     if(rect.equals(CCRectZero))
         m_pNormalImage->initWithFile(pFile);
     else
         m_pNormalImage->initWithFile(pFile,rect);
     addChild(m_pNormalImage);
     CCSize size = m_pNormalImage->getContentSize();
     setContentSize(size);
     m_pNormalImage->setPosition(ccp(size.width/2,size.height/2));
}
void wkButton::setSelectedImage(const char* pFile,CCRect rect)
{
    m_pSelectedImage = new CCSprite;
    if(rect.equals(CCRectZero))
        m_pSelectedImage->initWithFile(pFile);
    else
        m_pSelectedImage->initWithFile(pFile,rect);
    addChild(m_pSelectedImage);
    CCSize size = m_pSelectedImage->getContentSize();
    setContentSize(size);
    m_pSelectedImage->setPosition(ccp(size.width/2,size.height/2));
}
void wkButton::setDisabledImage(const char* pFile,CCRect rect)
{
    m_pDisabledImage = new CCSprite;
    if(rect.equals(CCRectZero))
        m_pDisabledImage->initWithFile(pFile);
    else
        m_pDisabledImage->initWithFile(pFile,rect);
    addChild(m_pDisabledImage);
    CCSize size = m_pDisabledImage->getContentSize();
    setContentSize(size);
    m_pDisabledImage->setPosition(ccp(size.width/2,size.height/2));
}
void wkButton::setSelectState(bool select)
{
   m_state = select;
}
void wkButton::ccTouchBegan     (CCTouch *pTouch, CCEvent *pEvent)
{
    setSelectState(true);
}
void wkButton::ccTouchEnded     (CCTouch *pTouch, CCEvent *pEvent)
{
    setSelectState(false);
}
void wkButton::ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent)
{
    setSelectState(false);
}
void wkButton::ccTouchSelect    (CCTouch *pTouch, CCEvent *pEvent)
{
    setSelectState(true);
}
void wkButton::ccTouchUnSelect  (CCTouch *pTouch, CCEvent *pEvent)
{
    setSelectState(false);
}
void wkButton::visit()
{
    if(isEnable())
    {
        if(m_state == 0 && m_pNormalImage)
        {
            m_pNormalImage->setVisible(true);
            CCSize size = m_pNormalImage->getContentSize();
            setContentSize(size);
            if(m_pSelectedImage) m_pSelectedImage->setVisible(false);
            if(m_pDisabledImage) m_pDisabledImage->setVisible(false);
        }
        else if(m_state == 1 && m_pSelectedImage)
        {
            m_pSelectedImage->setVisible(true);
            CCSize size = m_pSelectedImage->getContentSize();
            setContentSize(size);
            if(m_pNormalImage)  m_pNormalImage->setVisible(false);
            if(m_pDisabledImage) m_pDisabledImage->setVisible(false);
        }
    }
    else
    {
        if(m_pDisabledImage)
        {
            m_pDisabledImage->setVisible(true);
            CCSize size = m_pDisabledImage->getContentSize();
            setContentSize(size);
            if(m_pNormalImage)   m_pNormalImage->setVisible(false);
            if(m_pSelectedImage) m_pSelectedImage->setVisible(false);
        }
    }
    wkWidget::visit();
}
//////////////////////////////////////////////////////////////////////////
wkCheckButton::wkCheckButton()
{

}
wkCheckButton::~wkCheckButton()
{

}
void wkCheckButton::ccTouchBegan       (CCTouch *pTouch, CCEvent *pEvent)
{

}
void wkCheckButton::ccTouchEnded       (CCTouch *pTouch, CCEvent *pEvent)
{

}
void wkCheckButton::ccTouchCancelled   (CCTouch *pTouch, CCEvent *pEvent)
{

}
void wkCheckButton::ccTouchSelect      (CCTouch *pTouch, CCEvent *pEvent)
{

}
void wkCheckButton::ccTouchUnSelect    (CCTouch *pTouch, CCEvent *pEvent)
{

}
void wkCheckButton::visit()
{
    wkWidget::visit();
}
//////////////////////////////////////////////////////////////////////////
wkLabel::wkLabel()
{

}
wkLabel::~wkLabel()
{

}
//////////////////////////////////////////////////////////////////////////