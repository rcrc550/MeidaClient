#ifndef TCPNET_H
#define TCPNET_H
#include <process.h>
#include <winsock2.h>
class INetMediator
{
public:
    char szbuf[14];
    int port;
public:
    virtual void send_message()=0;
     virtual void setIpPoret()=0;
     virtual  void  dealMessage()=0;
};

class TcpNet
{
public:
    TcpNet();
};

#endif // TCPNET_H
