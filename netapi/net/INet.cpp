#include<INet.h>

bool INet::m_isLoadlib = false;

//ip long型向字符串转换
std::string INet::GetIPString( long ip )
{
    SOCKADDR_IN sockaddr;
    sockaddr.sin_addr.S_un.S_addr = ip;
    return inet_ntoa(sockaddr.sin_addr);
}

