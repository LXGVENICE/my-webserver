#pragma once
#include <string>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "processpool.hpp"

typedef struct run_status
{
    bool status;
    bool keep_alive;
}run_status;

class Cgi_conn
{
public:
    Cgi_conn(){}
    ~Cgi_conn(){}
    void init(int epollfd,int sockfd);
    void process();//建议返回一个结构体,改
private:
    static int m_epollfd;
    int m_sockfd;
    HttpRequest m_request;
    HttpResponse m_response;//later
};
