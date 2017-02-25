#pragma once
#include <unordered_map>
#include <string>

class HttpState
{
public:
    typedef uint16_t CODE;
    void set_code(CODE code){ m_code = code; }
    std::string get_state(){ return m_state[m_code]; }
private:
    CODE m_code;
    static std::unordered_map<CODE,std::string> m_state;
};

