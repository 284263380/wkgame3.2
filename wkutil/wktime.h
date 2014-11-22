#ifndef __WKTIME_H__
#define __WKTIME_H__
#include "wkpool.h"
#include "wkdefine.h"


class wktime : public wkpool
{
public:
    wktime();
    virtual ~wktime();
public:
    uint32 m_time;
};


#endif//__WKTIME_H__

