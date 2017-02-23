#pragma once
#include <string>
#include <unordered_map>

#define PATH "/home/web_server/html"
#define CRFL "\r\n"

class HttpResponse
{
public:
    bool parser(std::string line);
    std::string get_pkg();
private:
    bool first_parser(std::string &line);
    bool header_parser(std::string &line);
    void create_first();
private:
    HttpState m_state;
    std::string m_protocol;
    std::string m_resource;
    std::string m_first;
    std::unordered_map<std::string,std::stirng> m_header;
    std::string m_body;
};