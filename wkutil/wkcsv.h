#ifndef __WKCSV_H__
#define __WKCSV_H__
#include "wkpool.h"
#include "wkdefine.h"

class wkcsvItem;
class wkcsvColumn;
class wkcsv
{
public:
    wkcsv();
    virtual ~wkcsv();
    bool loadCsvFile2(const char* fullpath = NULL);
    bool loadCsvFile(const char* fullpath = NULL);
    bool exit();
    wkcsvItem* operator[](char* key);
    wkcsvColumn* getColumn(int idx);
    char* getColumnName(int idx);
    int   getColumnIdx(char* name);
    bool  analyseColumn(char* buff);
    bool  analyseLines(char* buff);
    void  analyse(char* buff,list<char*>& lstItem);
    void  removeTail(char* buff);
    wkcsvItem* getline(int idx);
    char* getItem(int line,char* name);
    int   getLineCnt();
public:
    wkcsvColumn*           m_columns;
    map<string,wkcsvItem*> m_mapDataLine;
    vector<wkcsvItem*>     m_lstDataLine;
    int                    m_configColumnIdx;
    int                    m_cntColumn;
    //int                    m_cntLine;
};
class wkcsvItem
{
public:
    wkcsvItem();
    wkcsvItem(wkcsv* csv);
    ~wkcsvItem();
    char** item;
    wkcsv* csv;
    int    cnt;
};
class wkcsvColumn
{
public:
    ~wkcsvColumn();
    char* item;
};






#endif//__WKCSV_H__

