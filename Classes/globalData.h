#pragma once
#include "wkcsv.h"
#include <map>
#include <string>
using namespace std;




struct EffectClass
{
    char  name[128];
    int   type;
    char  file[128];    //动画路径
    int   effStart;    //动画开始帧
    int   effCnt;      //动画帧数
    float effectDelay;//动画总时间
    int   loopCnt;    //
    bool  IsRestoreOrg;//播放完之后是否返回到第一帧
    char  plistPath[128];   
    char  pngPath[128];     
};

struct roleClass
{
    char name[128];
    int  type;
    char firstSprite[128];
};

class globalData
{
public:
    globalData();
    ~globalData();
    bool Init();
    EffectClass* resFindEffect(char* buff);
public:
    std::map<string,EffectClass> m_pEffectTable;
};

extern globalData* g_globalData;