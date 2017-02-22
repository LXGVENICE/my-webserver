#include <stdio.h>
#include "socket.hpp"
#include "cgi_conn.h"

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

    int listenfd = serfd.Getfd();
    ProcessPool* pool = ProcessPool::create(listenfd);
    if(pool == NULl)
        printf("processpool created fail\n");
    else
    {
        pool->run();
        //delete pool;
    }
    //close()
}