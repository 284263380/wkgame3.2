#ifndef __WKEVENT_H__
#define __WKEVENT_H__
#include "wkpool.h"
#include "wkdefine.h"



class wkevent : public wkpool
{
public:
    wkevent();
    virtual ~wkevent();
public:
    bool registerMsg();  
};




#endif//__WKEVENT_H__

