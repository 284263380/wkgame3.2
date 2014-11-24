#pragma once
#define NS_UI_BEGIN  namespace wkUI{
#define NS_UI_EN                   }
#define USING_NC_UI using namespace wkUI;

#include "base_nodes/CCNode.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "platform/CCAccelerometerDelegate.h"
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "cocos2d.h"
#include <string>
USING_NS_CC;
NS_UI_BEGIN

class wkWidget;
//typedef void (*_wkWidgetOnClick)(wkWidget*,uint32_t,uint32_t);

using namespace std;

class wkWidgetSlot : public CCNodeRGBA, public CCTouchDelegate
{
public:
    static wkWidgetSlot* create();
public:
    wkWidgetSlot();
    ~wkWidgetSlot();
    virtual bool init();
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void visit();
public:
    wkWidget* m_pSelectWidget;
    int stateWidget;
public:
    enum eStateWidget
    {
        esw_init        = 0,
        esw_select      = 1,
        esw_unselect    = 2,
    };
};
class wkWidget : public CCNodeRGBA
{
public:
    wkWidget();
    virtual ~wkWidget();
    virtual bool init();
    virtual bool init(CCSize cc);
    static wkWidget *create(void);
public:
    virtual void setTouchEnable(bool enable = true);
    virtual bool getTouchEnable() { return m_bIsTouchEnabled;}

    virtual void ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

    virtual void ccTouchSelect(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchUnSelect(CCTouch *pTouch, CCEvent *pEvent){};
    
    bool isEnable();
    void setEnable(bool v);
    virtual void onEnableOnChange(bool v){}
    void setBackground(const char* path,CCRect rect = CCRectZero);
    virtual void visit();
    void setText(string& text);
    string getText();
public:
    std::string  m_name;
    bool         m_bIsTouchEnabled;      //touch enable
    bool         m_bEnable;              //state enable
    CCSprite*    m_background;           //background
    string       m_text;                 //text
    string       m_fontName;             //font name
    int          m_fontSize;             //font size
    int          m_textAlign;            //text align:0-left 1-middle 2-right 
    int          m_textAlign2;           //0-top 1-center 2-bottom
};
class wkButton : public wkWidget
{
public:
    static wkButton *create();
    static wkButton *create(const char* normalImg,const char* selectImg,const char* disableImg);
public:
    wkButton();
    virtual ~wkButton();
    bool init();
    bool initWidthFile              (const char* normalImg,const char* selectImg,const char* disableImg);
    void setNormalImage             (const char* pFile,CCRect rect = CCRectZero);
    void setSelectedImage           (const char* pFile,CCRect rect = CCRectZero);
    void setDisabledImage           (const char* pFile,CCRect rect = CCRectZero);
    virtual void ccTouchBegan       (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded       (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled   (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchSelect      (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchUnSelect    (CCTouch *pTouch, CCEvent *pEvent);
    virtual void visit();
    void setSelectState(bool select);
public:
    CCSprite* m_pNormalImage;
    CCSprite* m_pSelectedImage;
    CCSprite* m_pDisabledImage;
    int       m_state;//0:unselect 1:select 2:disable
};
class wkCheckButton : public wkWidget
{
public:
    wkCheckButton();
    virtual ~wkCheckButton();
public:
    virtual void ccTouchBegan       (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded       (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled   (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchSelect      (CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchUnSelect    (CCTouch *pTouch, CCEvent *pEvent);
    virtual void visit();
public:
    CCSprite* m_pUnChecked;
    CCSprite* m_pUnCheckedOn;
    CCSprite* m_pChecked;
    CCSprite* m_pCheckedOn;
    CCSprite* m_pDisableUnChecked;
    CCSprite* m_pDisableChecked;
};
class wkLabel
{
public:
    wkLabel();
    virtual ~wkLabel();
};
NS_UI_EN