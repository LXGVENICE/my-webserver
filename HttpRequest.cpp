#include "HttpRequest.hpp"
#include <iostream>

void HttpRequest::append(char buf[],int ret)
{
    m_recv_packet.append(buf,ret);
}

void HttpRequest::clear()
{
    m_recv_packet.clear();
    m_recv_packet.shrink_to_fit();
}

int HttpRequest::get_next_pos()
{
    if(m_recv_packet.empty()) 
        return -1;
    else
        return m_recv_packet.find("\r\n");
}

int HttpRequest::get_next_line()//pos 为 0 则为头,大于0 则为头部 ,-1 则为空
{
    size_t pos = get_next_pos();
    //printf("pos: %d\n",pos);
    if(m_recv_packet.empty() || pos == std::string::npos)
        m_recv_packet = "";//////fix it's memory
    else if(pos == 0)
    {
        m_recv_packet.erase(0,2);
        m_line = m_recv_packet;
        m_recv_packet = "";
        //std::cout<<"pos00:"<<m_line<<std::endl;
    }
    else
    {
        m_line = m_recv_packet.substr(0,pos);
        m_recv_packet.erase(0,pos+2);
        //std::cout<<m_line<<std::endl;
    }
    return pos;
}

std::string HttpRequest::get_line()
{
    return m_line;
}