#include "socket.hpp"
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


Socket::Socket()
{
        _sockfd = socket(AF_INET,SOCK_STREAM,0);
        bzero(&_socketaddr,sizeof(_socketaddr));
}

Socket::~Socket(){ close(_sockfd); }

int Socket::Getfd(){ return _sockfd; }

void Socket::CreateAddr(const char *ip,int port)
{
    _ip = ip;
    _port = port;
    _socketaddr.sin_family = AF_INET;
    _socketaddr.sin_addr.s_addr = inet_addr(_ip);
    _socketaddr.sin_port = htons(_port);
}

cosnt char* Socket::GetIP(){ return _ip; }

int Socket::GetPort(){ return _port; }

bool Socket::Bind()
{
    if(bind(_sockfd,(struct sockaddr*)&_socketaddr,sizeof(_socketaddr)) == -1)
    {
        perror("bind fail:");
        return false;
    }
    return true;
}

bool Socket::Listen(int num)
{
    if(listen(_sockfd,num) == -1)
    {
        perror("listen fail:");
        return false;
    }
    return true;
}

int Socket::Accept()
{
    return accept(_sockfd,NULL,0);
}

bool Socket::Connect()
{
    if(connect(_sockfd,(struct sockaddr*)&_socketaddr,sizeof(_socketaddr)) == -1)
    {
        perror("connect error:");
        return false;
    }
    return true;
}
