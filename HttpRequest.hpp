#pragma once
#include <vector>
#include <string>

class HttpRequest
{
public:
    HttpRequest();
    void append();
    void clear();
    int is_next_line();
    int get_next_line(std::string &head);
private:
    stirng m_recv_parser;
};