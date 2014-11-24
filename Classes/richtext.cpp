#include "richtext.h"


wkRichTextItem::wkRichTextItem()
{

}
wkRichTextItem::~wkRichTextItem()
{

}
//////////////////////////////////////////////////////////////////////////
wkRichTextLine::wkRichTextLine()
{

}
wkRichTextLine::~wkRichTextLine()
{

}
//////////////////////////////////////////////////////////////////////////
wkRichText* wkRichText::create()
{
    wkRichText * ret = new wkRichText();
    if (ret)
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
    return ret;
}
wkRichText::wkRichText()
{
    this->setContentSize(cocos2d::Size(100,100));
}
wkRichText::~wkRichText()
{

}
void wkRichText::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    
}