#include "cgi_conn.hpp"
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <iostream>

int Cgi_conn::m_epollfd = -1;

void Cgi_conn::init(int epollfd,int sockfd)
{
    m_epollfd = epollfd;
    m_sockfd = sockfd;
}

void Cgi_conn::process()
{
    printf("new connetion has benn estabilshed\n");
    char buf[1024] = {0};
    int ret = 0;
    do
    {
        ret = recv(m_sockfd,buf,sizeof(buf),0);
        //printf("%d",ret);
        if(ret < 0)
        {
            perror("http response recv fail:");
            m_request.clear();
            //m_http_packet.shrink_to_fit();
            return;
        }
        m_request.append(buf,ret);
        bzero(buf,sizeof(buf));
    }
    while((ret > 0) && (errno == EAGAIN));
    
    std::string head;
    while(ret != -1)
    {
        ret = m_request.get_next_line(head);
        std::cout<<head<<std::endl;
    }
    //if(ret)
    //removefd(m_epollfd,m_sockfd);
}