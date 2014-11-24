#pragma once
#include "cocos2d.h"
#include <vector>

class Renderer;
class Mat4;
class wkRichTextItem
{
public:
    wkRichTextItem();
    ~wkRichTextItem();
};
class wkRichTextLine
{
public:
    wkRichTextLine();
    ~wkRichTextLine();
public:
    std::vector<wkRichTextItem> m_vecItems;
};
class wkRichText : public cocos2d::Node
{
public:
    wkRichText();
    ~wkRichText();
    static wkRichText* create();
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
public:
    std::vector<wkRichTextLine> m_vecLines;
};
