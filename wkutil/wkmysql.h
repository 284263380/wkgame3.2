#ifndef __WKMYSQL_H__
#define __WKMYSQL_H__

#ifdef WIN32
    #include <WinSock2.h>
//#elif defined(__GNUG__)
#endif
//#include "include/mysql.h"


class wkMysql
{
public:
    wkMysql();
    ~wkMysql();
    bool connectMysql(const char *host,const char *user,const char *passwd,const char *db,unsigned int port,const char *unix_socket,unsigned long clientflag);
public:
    int config_max_thread;//最大线程数
    char mBuffHost[64];
    char mBuffPwd[16];
    char mBuffdb[32];
    int  mPort;
    //设置断线重连
};




#endif // __WKMYSQL_H__
