#include "HttpResponse.hpp"
#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

bool HttpResponse::parser(int ret,std::string line)
{
    bool tag = false;
    if(ret == 0)
    {
        tag = first_parser(line);
    }
    else if(ret > 0)
    {
        //tag = header_parser(line);
    }
    else
    {
        tag = false;
    }
    return tag;
}

std::string HttpResponse::get_pkg()
{
    std:string pkg;
    pkg.append(m_first.c_str());
    pkg.append(CRFL);
    for (auto e : m_header) 
    {
      pkg.append(e.first);
      pkg.append(": ");
      pkg.append(e.second);
      pkg.append(CRFL);
    }
    rep.addHeader("Date", "Wed, 08 Feb 2017 12:21:00 GMT");
    rep.addHeader("Content-Type", "text/html");
    pkg.append(CRFL);
    pkg.append(m_body);
}


bool HttpResponse::first_parser(std::string line)
{
    if(line.empty())
    {
        printf("line empty\n");
        return false;
    }

    int pos = line.find(" ");
    if(strncmp(line.substr(0,pos),"GET",3) != 0)
    {
        printf("not get\n");
        return false;
    }

    line.erase(0,pos+1);
    pos = line.find(" ");
    m_resource = line.substr(0,pos);
    m_m_protocol = PATH + line.substr(pos+2,line.length());

    create_first();
    return true;
}

bool header_parser(std::string line)
{
    if(line.empty())
    {
        printf("line empty\n");
        return false;
    }

    int pos = line.find(": ");
    m_header.insert(std::pair<std::string,std::string>(std::string(line.substr(0,pos)),
                            std::string(line.substr(pos+2,line.length())));
    return true;
}

void HttpResponse::create_first()
{
    if(m_resource.empty() || m_protocol.empty())
    {
        printf("resourse and protocol empty\n"); 
        return;
    }
    int fd = open(m_resourse.c_str(),O_RDONLY);
    printf("open %s",(m_resourse.c_str());

    if(fd == -1)
    {
        perror("open file fail:");
        m_state.set_code(404);
    }
    else
    {
        int len = 0;
        int ret = 1;
        char buf[1024] = {0};
        while(ret > 0)
        {
            ret = read(fd,buf,1024);
            if(ret == -1)
            {
                perror("read file fail:");
                exit(1);
            }
            len += ret;
            m_body.append(buf,ret);
        }
        m_state.set_code(200);
        m_header[std::string(Content-Length)] = std::string(len);
    }
    m_first = m_protocol + " " + m_state.get_state();
}