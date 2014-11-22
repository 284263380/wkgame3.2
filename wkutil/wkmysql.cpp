#include "wkdefine.h"
#include "wkmysql.h"

#pragma comment(lib,"lib/libmysql.lib")



wkMysql::wkMysql()
{

}
wkMysql::~wkMysql()
{

}
bool wkMysql::connectMysql(const char *host,const char *user,const char *passwd,const char *db,unsigned int port,const char *unix_socket,unsigned long clientflag)
{
//     MYSQL mDB;
//     mysql_init(&mDB);
//     if(!mysql_real_connect(&mDB,"192.168.16.34","root","root","game",3306,NULL,0))
//     {
//         perror("error");
//         return false;
//     }
    return true;
}