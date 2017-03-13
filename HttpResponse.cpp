#include "HttpResponse.hpp"
#include <time.h>
#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>


void HttpResponse::clear()
{
    m_protocol.clear();//HTTP协议版本
    m_resource.clear();//HTTP请求资源
    m_first.clear();
    m_header.clear();
    m_body.clear();
}

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

std::string HttpResponse::set_time()
{
    std::string gtime = "Date: ";
    time_t timep = time(NULL);
    struct tm* p = gmtime(&timep);
    switch(p->tm_wday)
    {
        case 1:gtime.append("Mon, ");break;
        case 2:gtime.append("Tues, ");break;
        case 3:gtime.append("Wed, ");break;
        case 4:gtime.append("Thur, ");break;
        case 5:gtime.append("Fri, ");break;
        case 6:gtime.append("Sat, ");break;
        case 0:gtime.append("Sun, ");break;
        default:break;
    }
    gtime.append(std::to_string(p->tm_mday));
    switch(p->tm_mon)
    {
        case 0:gtime.append(" Jan ");break;
        case 1:gtime.append(" Feb ");break;
        case 2:gtime.append(" Mar ");break;
        case 3:gtime.append(" Apr ");break;
        case 4:gtime.append(" May ");break;
        case 5:gtime.append(" Jun ");break;
        case 6:gtime.append(" Jul ");break;
        case 7:gtime.append(" Aug ");break;
        case 8:gtime.append(" Sep ");break;
        case 9:gtime.append(" Oct ");break;
        case 10:gtime.append(" Nov ");break;
        case 11:gtime.append(" Dec ");break;
        default:break;
    }
    gtime.append(std::to_string(p->tm_year+1900));
    gtime += " " + std::to_string(p->tm_hour) + ":" + std::to_string(p->tm_min) + ":" + std::to_string(p->tm_sec) + " GMT\r\n";
    return gtime; 
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
    
    pkg.append(set_time());
    pkg.append("Content-Type: text/html\r\n");
    pkg.append(CRFL);
    pkg.append(m_body);
    return pkg;
}


bool HttpResponse::first_parser(std::string line)
{
    std::cout<<"first_parser:"<<line<<std::endl;
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
    printf("open %s\n",m_resource.c_str());

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