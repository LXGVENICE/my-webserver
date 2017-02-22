#include "HttpRequest.hpp"

void HttpRequest::append(char buf[],int ret)
{
    m_recv_parser.append(buf,ret);
}

void HttpRequest::clear()
{
    m_recv_parser.clear();
    m_recv_parser.shrink_to_fit();
}

int HttpRequest::get_next_pos()
{
    if(m_recv_parser.empty()) 
        return -1;
    else
        return m_recv_parser.find("\r\n");
}

int HttpRequest::get_next_line(std::string &head)
{
    int pos = get_next_pos();
    if(pos == -1)
        head = "";
    else if(pos == 0)
    {
        m_recv_parser.erase(0,2);
        head = m_recv_parser;
        m_recv_parser.shrink_to_fit();//??
    }
    else
    {
        head = m_recv_parser.substr(0,pos);
        m_recv_parser.erase(0,pos+2);
    }
    
    return pos;
}