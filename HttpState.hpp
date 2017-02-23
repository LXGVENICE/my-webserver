#pragma once
#include <unordered_map>

class HTTPState
{
public:
    typedef uint16_t CODE;
    void set_code(CODE code){ m_code = code; }
    std::string get_state(){ retur m_state[CODE]; }
private:
    CODE m_code;
    static std::unordered_map<CODE,std::string> m_state;
};