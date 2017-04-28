#include <stdio.h>
#include "socket.hpp"
#include "processpool.hpp"
#include "cgi_conn.hpp"

int main()
{
    Socket serfd;
    serfd.Setsockopt(32);
    serfd.CreateAddr("10.154.156.125",80);
    if(!serfd.Bind())
    {
        perror("bind failed:");
        exit(1);
    }
    printf("bind %s successed\n", serfd.GetIP());
    if(!serfd.Listen(5))
    {
        perror("listen failed:");
        exit(1);
    }
    printf("listen %s:%d successed\n", serfd.GetIP(), serfd.GetPort());

    int listenfd = serfd.Getfd();

    ProcessPool* pool = ProcessPool::create(listenfd,8);
    if(pool == NULL)
        printf("processpool created fail\n");
    else
    {
        pool->run();
        //delete pool;
    }
    //close()
}
