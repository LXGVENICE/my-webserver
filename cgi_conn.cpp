#include "cgi_conn.hpp"
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>


Cgi_conn::Cgi_conn()

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
        if(ret < 0)
        {
            perror("http response recv fail:");
            m_request.clear();
            //m_http_packet.shrink_to_fit();
            return;
        }
        m_request.append(buf,ret);
        bzero(buf,size(buf));
    }
    while(len > 0);
    
    std::string head;
    while(ret != -1)
    {
        ret = m_request.get_next_line(head);
        std::cout<<head<<std::endl;
    }
    //if(ret)

}