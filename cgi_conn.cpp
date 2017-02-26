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
            perror("http response recv fail");
            m_request.clear();
            //m_http_packet.shrink_to_fit();
            return;
        }
        m_request.append(buf,ret);
        bzero(buf,sizeof(buf));
        printf("%d\n",errno);
    }
    while((ret > 0) && (errno == EAGAIN));
    
    if(m_request.get_next_line() == -1) return;
    m_response.first_parser(m_request.get_line());

    bool tag = true;
    while(tag)
    {
        tag = m_response.parser(m_request.get_next_line(),m_request.get_line());
    }

    std::string pkg = m_response.get_pkg();
    std::cout<<pkg<<std::endl;
    ret = send(m_sockfd,pkg.data(),pkg.length(),0);
    if(ret < 0)
    {
        perror("send fail");
    }
}