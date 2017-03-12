#include "HttpResponse.hpp"
#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

bool HttpResponse::parser(int ret,std::string line)
{
    bool tag = false;

    if(line.empty())
    {
        printf("line empty\n");
        return tag;
    }
    
    if(ret == 0)
    {
        //tag = body_parser(line);
        return true;
    }
    else if(ret > 0)
    {
        //m_header.insert(make_pair(line.substr(0,pos),line.substr(pos+2,line.length())));
        tag = header_parser(line);
        return tag;
    }
    else
    {
        return tag;;
    }
}

std::string HttpResponse::get_pkg()
{
    std::string pkg;
    pkg.append(m_first.c_str());
    pkg.append(CRFL);
    for (auto e : m_header) 
    {
      pkg.append(e.first);
      pkg.append(": ");
      pkg.append(e.second);
      pkg.append(CRFL);
    }
    pkg.append("Date: Wed, 08 Feb 2017 12:21:00 GMT\r\n");
    pkg.append("Content-Type: text/html\r\n");
    pkg.append(CRFL);
    pkg.append(m_body);
    return pkg;
}


bool HttpResponse::first_parser(std::string line)
{
    if(line.empty())
    {
        printf("line empty\n");
        return false;
    }

    int pos = line.find(" ");
    if(strncmp(line.substr(0,pos).c_str(),"GET",3) != 0)
    {
        printf("not get\n");
        return false;
    }

    line.erase(0,pos+1);
    pos = line.find(" ");
    if(pos == -1) return false;
    if(line.substr(0,pos) == "/")
        m_resource = PATH + std::string("/index.html");
    else
        m_resource = PATH + line.substr(0,pos);
    line.erase(0,pos+1);
    printf("resourse:%s\n",m_resource.c_str());

    m_protocol = line;
    printf("protocol:%s\n",m_protocol.c_str());

    create_first();
    return true;
}

bool HttpResponse::header_parser(std::string &line)
{
    if(line.empty())
    {
        printf("line empty\n");
        return false;
    }

    int pos = line.find(": ");
    if(pos == -1) return false;

    std::string key = line.substr(0,pos);
    std::string value = line.substr(pos+2,line.length());
    if(key == "Connection")
    {
        if(value == "keep-alive")
            keep_alive = true;
        else
            keep_alive = false;
    }
    return true;
}

void HttpResponse::create_first()
{
    if(m_resource.empty() || m_protocol.empty())
    {
        printf("resourse and protocol empty\n"); 
        return;
    }
    int fd = open(m_resource.c_str(),O_RDONLY);
    printf("open %s",m_resource.c_str());

    if(fd == -1)
    {
        perror("open file fail");
        m_state.set_code(404);
        m_resource = PATH + std::string("/errno.html");
        fd = open(m_resource.c_str(),O_RDONLY);
    }
    else
    {
        m_state.set_code(200);
    }

    int len = 0;
    int ret = 1;
    char buf[1024] = {0};
    while(ret > 0)
    {
        ret = read(fd,buf,1024);
        if(ret == -1)
        {
            perror("read file fail");
            exit(1);
        }
        len += ret;
        m_body.append(buf,ret);
    }
    
    m_header[std::string("Content-Length")] = std::to_string(len);
    
    m_first = m_protocol + " " + m_state.get_state();
}