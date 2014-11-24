#pragma once
#include "wkcsv.h"
#include <map>
#include <string>
using namespace std;




struct EffectClass
{
    char  name[128];
    int   type;
    char  file[128];    //����·��
    int   effStart;    //������ʼ֡
    int   effCnt;      //����֡��
    float effectDelay;//������ʱ��
    int   loopCnt;    //
    bool  IsRestoreOrg;//������֮���Ƿ񷵻ص���һ֡
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