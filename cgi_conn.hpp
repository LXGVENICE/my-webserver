#pragma once
#include <string>

class Cgi_conn
{
public:
    Cgi_conn(){}
    ~Cgi_conn(){}
    void init(int epollfd,int sockfd);
    void process();
private:
    static int m_epollfd;
    int m_sockfd;
    //string m_recv_packet;
    //string m_send_packet;
    HttpRequest m_request;
    HttpResponse m_response;
}

int Cgi_conn::m_epollfd = -1;