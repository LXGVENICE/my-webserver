#pragma once
#include <string>
#include <unordered_map>
#include "HttpState.hpp"

#define PATH "/home/venice/web-server/html"
#define CRFL "\r\n"

//enum HTTPMethod
//{
//  GET, POST, DELETE, PUT, HEAD, 
//  INVAILD;
//}

class HttpResponse
{
public:
    HttpResponse():keep_alive(true){}
    bool parser(int ret,std::string line);
    bool first_parser(std::string line);
    std::string get_pkg();
    bool is_keep_alive(){ return keep_alive; }
private:
    bool header_parser(std::string &line);
    void create_first();
    std::string set_time();
private:
    HttpState m_state;//HTTP状态码
    std::string m_protocol;//HTTP协议版本
    std::string m_resource;//HTTP请求资源
    bool keep_alive;
    std::string m_first;
    std::unordered_map<std::string,std::string> m_header;
    std::string m_body;
};