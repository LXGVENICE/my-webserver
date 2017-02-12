#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <strings.h>
#include <sys/socket.h>
#include "HttpResponse.hpp"
#include "Util.hpp"
using namespace std;

#define IP = "127.0.0.1";
cosnt int PORT = 8000;

int main()
{
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd == -1)
    {
        perror("socket failed");
        exit(1);
    }

    struct sockaddr_in listenAddr;
    bzero(&listenAddr,sizeof(listenAddr));
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_port = htons(PORT);
    listenAddr.sin_addr.s_addr = inet_addr(IP);

    if(bind(listenfd,(struct sockaddr*)listenAddr,sizeof(listenAddr) == -1)
    {
        perror("bind failed");
        exit(1);
    }

    printf("bind %s successed\n", IP);

    if(listen(listenfd,5) == -1)
    {
        perror("listen failed");
        exit(1);
    }

    printf("listen %s:%d successed\n", IP, PORT);
}