#ifndef __WKPOOL_H__
#define __WKPOOL_H__

class wkpool
{
public:
    wkpool();
    virtual ~wkpool();
    void* operator new(size_t size);
};





#endif//__WKPOOL_H__

