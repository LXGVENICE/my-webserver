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
    int get_next_line();
    std::string get_line();
private:
    std::string m_recv_packet;
    std::string m_line;
};