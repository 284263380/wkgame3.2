#ifndef __WKDEFINE_H__
#define __WKDEFINE_H__


//include std
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

//define type
typedef  unsigned char      uint8;
typedef  unsigned short     uint16;
typedef  unsigned int       uint32;
typedef  unsigned long long uint64;
               
typedef  char               int8;
typedef  short              int16;
typedef  int                int32;
typedef  long long          int64;


#ifndef size_t
    #define size_t uint32
#endif


//string  function 
//

#define __if_break(x)   {if(x)break;}




#endif//__WKDEFINE_H__

