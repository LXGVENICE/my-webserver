#pragma once
#include <vector>
#include <string>

class HttpRequest
{
public:
    HttpRequest(){};
    void append(char buf[],int ret);
    void clear();
    int get_next_pos();
    int get_next_line(std::string &head);
private:
    std::string m_recv_parser;
};