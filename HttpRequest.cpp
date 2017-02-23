#include "HttpRequest.hpp"

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
    int pos = get_next_pos();
    if(m_recv_packet.empty() || pos == -1)
        m_recv_packet.swap("");
    else if(pos == 0)
    {
        m_recv_packet.erase(0,2);
        line = m_recv_packet;
        m_recv_packet.swap("");
    }
    else
    {
        line = m_recv_packet.substr(0,pos);
        m_recv_packet.erase(0,pos+2);
    }
    return pos;
}

std::stirng HttpRequest::get_line()
{
    return line;
}

const char* HttpRequest::parser(int ret)
{
    if(ret == 0 || m_line.empty())
    {
        m_line.swap("");
        return NULL;
    } 
    int pos = m_line.find(": ");
    if(pos == -1)
    {
        method_parser(m_line);
    }
    else
    {

    }
}

std::string& HttpRequest::method_parser(std::string &method)
{
    int pos = method.find(" ");
    if(pos == -1)
        return NULL;
    else if(method.substr(0,pos) == "GET")
    {
        method.erase(0,pos+1);
        pos = method.find(" ");
        method.erase(pos,method.length());
        return method
    }
}