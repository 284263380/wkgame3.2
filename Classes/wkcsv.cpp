#include "wkcsv.h"


const unsigned int FILE_MAX_LINE = 50;
wkcsvItem::wkcsvItem()
{
    item = NULL;
    csv  = NULL;
}
wkcsvItem::wkcsvItem(wkcsv* csv)
{
    this->csv = csv;
}
wkcsvItem::~wkcsvItem()
{
    if(item)
    {
        for (int i=0;i<cnt;i++)
        {
            char* buff = item[i];
            if(!buff)
                continue;
            delete buff;
        }
        delete item;
        item = NULL;
    }
}
//////////////////////////////////////////////////////////////////////////
wkcsv::wkcsv()
{
    m_configColumnIdx = 0;
    m_cntColumn  = 0;
    m_columns    = NULL;
}
wkcsv::~wkcsv()
{
    delete[] m_columns;
    m_cntColumn = 0;
    for (vector<wkcsvItem*>::iterator iter = m_lstDataLine.begin();iter!=m_lstDataLine.end();++iter)
    {
        wkcsvItem* v = *iter;
        if(!v)
            continue;
        delete v;
        v = NULL;
    }
    m_lstDataLine.clear();
    m_mapDataLine.clear();
}
wkcsvColumn::~wkcsvColumn()
{
    if(item)
    {
        delete item;
        item = NULL;
    }
}
bool wkcsv::loadCsvFile2(const char* fullpath)
{
    if(!fullpath || strlen(fullpath) ==0)
        return false;
    FILE* file =NULL;
    file = fopen(fullpath,"rb");
    if(!file)
        return false;
    int lineCurrent = 0;
    unsigned int lenLine = FILE_MAX_LINE;
    char* buffLine = new char[lenLine];
    do 
    {
        fpos_t posBegin = 0;
        fpos_t posEnd   = 0;
        fgetpos(file,&posBegin);
        memset(buffLine,0,lenLine);
        int c = getc(file);
        if(c == EOF)
            break;
        do
        {
            if( c != '\"')
            {
                while((c = getc(file)) != EOF)
                {
                    if(c == '\n')
                        goto GOTO_001;
                    if(c == ',')
                        break;
                };
            }
            else
            {
                int cnt = 1;
                while( (c = getc(file)) != EOF)
                {
                    if(c == '\n' && cnt%2 == 0)
                        goto GOTO_001;
                    if(c == ',' && cnt%2 == 0)
                        break;
                    if(c == '\"')
                        cnt ++;
                };
            }
            c = getc(file);
        }while(true);
GOTO_001:
        fgetpos(file,&posEnd);
        unsigned int tmpLen = int(posEnd - posBegin); 
        if(tmpLen > lenLine)
        {
            delete []buffLine;
            lenLine = int(posEnd - posBegin)+1;
            buffLine = new char[lenLine];
            memset(buffLine,0,lenLine);
        }
        fseek(file,(int)posBegin,SEEK_SET);
        for (int i=0;i<(int)tmpLen;i++)
            buffLine[i] = (char)getc(file);
        if(lineCurrent==m_configColumnIdx)
            analyseColumn(buffLine);
        else
            analyseLines(buffLine);
        lineCurrent++;
    } while (true);
    delete []buffLine;
    buffLine = NULL;
    return true;
}
bool wkcsv::loadCsvFile(const char* fullpath)
{
    if(!fullpath || strlen(fullpath) ==0)
        return false;
    FILE* file =NULL;
    file = fopen(fullpath,"rt");
    if(!file)
        return false;
    int lineCurrent = 0;
    int   lenLine = FILE_MAX_LINE;
    char* buffLine = new char[lenLine];
    do 
    {
        fpos_t posBegin = 0;
        fgetpos(file,&posBegin);
        memset(buffLine,0,lenLine);
        if(!fgets(buffLine,lenLine,file))
            break;
        do
        {
            if(buffLine[strlen(buffLine)-1] == '\n')
                break;
            memset(buffLine,0,lenLine);
            fgets(buffLine,lenLine,file);
        } while (true);
        fpos_t posEnd = 0;
        fgetpos(file,&posEnd);
        fseek(file,(long)posBegin,SEEK_SET);
        if(posEnd-posBegin >  lenLine)
        {
            delete []buffLine;
            lenLine = int(posEnd-posBegin);
            buffLine = new char[lenLine];
        }
        memset(buffLine,0,lenLine);
        fgets(buffLine,lenLine,file);
        if(m_configColumnIdx == lineCurrent)
            analyseColumn(buffLine);
        else
           analyseLines(buffLine);
        
        lineCurrent++;
    } while (true);
    delete[] buffLine;
    buffLine = NULL;
    return true;
}
wkcsvItem* wkcsv::operator[](char* key)
{
   map<string,wkcsvItem*>::iterator iter = m_mapDataLine.find(key);
   if(iter == m_mapDataLine.end())
       return NULL;
   return iter->second;
}
void  wkcsv::dealTail(char* buff)
{
    if(!buff)
        return;
    int len = strlen(buff);
    if(len <=1 )
        return;
    if(len>=2)
    {
        if(buff[len-2] =='\r' && buff[len-1] =='\n')
        {
            buff[len-2] = '\n';
            buff[len-1] = '\0';
        }
    }
}
bool wkcsv::analyseColumn(char* buff)
{
    dealTail(buff);
    list<char*> lstItems;
    analyse(buff,lstItems);
    int len = lstItems.size();
    m_columns = new wkcsvColumn[len];
    memset(m_columns,0,sizeof(wkcsvColumn)*len);
    for (list<char*>::iterator iter = lstItems.begin();iter!=lstItems.end();++iter)
        m_columns[m_cntColumn++].item = *iter;
    return true;
}
bool wkcsv::analyseLines(char* buff)
{
    dealTail(buff);
    list<char*> lstItems;
    analyse(buff,lstItems);
    wkcsvItem* line = new wkcsvItem;
    line->cnt = lstItems.size();
    line->csv = this;
    line->item = new char*[line->cnt];
    int i = 0;
    for (list<char*>::iterator iter = lstItems.begin();iter!=lstItems.end();++iter)
        line->item[i++] = *iter;
    m_mapDataLine[lstItems.front()]=line;
    m_lstDataLine.push_back(line);
    return true;
}
void wkcsv::analyse(char* buff,list<char*>& lstItem)
{
    int len = strlen(buff);
    for (int i=0;i<len;i++)
    {
        char* buffItem = &buff[i];
        if(buff[i] != '\"')
        {
            while(true)
            {
                if(buff[i] == '\n')
                {
                    buff[i] ='\0';
                    break;
                }
                if(buff[i] == ',')
                {
                    buff[i] ='\0';
                    break;
                }
                i++;
            };
        }
        else
        {
            int numQuotation = 1;
            i++;
            int pos = i;
            buffItem = &buff[pos];
            do 
            {
                buff[pos]=buff[i];
                if( buff[i] ==',' && numQuotation%2==0)
                {
                    buff[i]='\0';
                    buff[pos]='\0';
                    break;
                }
                else if(buff[i] == '\n' && numQuotation%2==0)
                {
                    buff[i]='\0';
                    buff[pos]='\0';
                    break;
                }
                else if(buff[i] =='\"')
                {
                    numQuotation++;
                    if(numQuotation%2 ==0)
                        pos--;
                }
                i++;
                pos++;
            } while (true);
        }
        char* buffNew = new char[strlen(buffItem)+1];
        strcpy(buffNew,buffItem);
        lstItem.push_back(buffNew);
    }
}
wkcsvColumn* wkcsv::getColumn(int idx)
{
    if(idx>m_cntColumn)
        return NULL;
    return &m_columns[idx];
}
char* wkcsv::getColumnName(int idx)
{
    wkcsvColumn* col = getColumn(idx);
    if(col)
        return col->item;
    return NULL;
}
int   wkcsv::getColumnIdx(char* name)
{
    for (int i=0;i<m_cntColumn;i++)
    {
        if(strcmp(m_columns[i].item,name)==0)
            return i;
    }
    return -1;
}
wkcsvItem* wkcsv::getline(int idx)
{
    if(idx<0)
        return NULL;
    if(idx >= (int)m_lstDataLine.size())
        return NULL;
    return m_lstDataLine[idx];
}
int wkcsv::getLineCnt()
{
    return m_lstDataLine.size();
}
char* wkcsv::getItem(int line,char* name)
{
    wkcsvItem* item = getline(line);
    if(!item)
        return NULL;
    int idx = getColumnIdx(name);
    if(idx == -1)
        return NULL;
    return item->item[idx];
}