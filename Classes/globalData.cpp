#include <stdlib.h>
#include "globalData.h"



globalData* g_globalData = NULL;
globalData::globalData()
{

}
globalData::~globalData()
{

}
bool globalData::Init()
{
    wkcsv* csv = new wkcsv;
    csv->loadCsvFile2("data\\effect.csv");
    for (int i=0;i<csv->getLineCnt();i++)
    {
        EffectClass effectClass;
        memset(&effectClass,0,sizeof(EffectClass));
        char* buff = csv->getItem(i,"name");
        strcpy(effectClass.name,buff);

        buff = csv->getItem(i,"type");
        effectClass.type = atoi(buff);

        buff = csv->getItem(i,"file");
        strcpy(effectClass.file,buff);

        buff = csv->getItem(i,"effStart");
        effectClass.effStart = atoi(buff);

        buff = csv->getItem(i,"effCnt");
        effectClass.effCnt   = atoi(buff);

        buff = csv->getItem(i,"effectDelay");
        effectClass.effectDelay   = atof(buff);

        buff = csv->getItem(i,"IsRestoreOrg");
        effectClass.IsRestoreOrg  = atoi(buff)?true:false;

        buff = csv->getItem(i,"loopCnt");
        effectClass.loopCnt  = atoi(buff);

        buff = csv->getItem(i,"plistPath");
        if(buff)
            strcpy(effectClass.plistPath,buff);

        buff = csv->getItem(i,"pngPath");
        if(buff)
            strcpy(effectClass.pngPath,buff);

        m_pEffectTable.insert(make_pair(effectClass.name,effectClass));
    }
    delete csv;
    return true;
}
EffectClass* globalData::resFindEffect(char* buff)
{
    std::map<string,EffectClass>::iterator iter = m_pEffectTable.find(buff);
    if( iter == m_pEffectTable.end())
        return NULL;
    return &iter->second;
}
