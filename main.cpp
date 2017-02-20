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

#include "socket.hpp"


int main()
{
    Socket serfd;
    serfd.CreateAddr("127.0.0.1",8080);
    if(!serfd.Bind())
    {
        perror("bind failed");
        exit(1);
    }
    printf("bind %s successed\n", serfd.GetIP());
    if(serfd.listen(5))
    {
        perror("listen failed");
        exit(1);
    }
    printf("listen %s:%d successed\n", serfd.GetIP(), serfd.GerPort());


    while(1)
}