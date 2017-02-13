#program once

class HttpState
{
public:
    typedef uint16_t CODE;

    static const CODE HTTP_200 = 200;
    static const CODE HTTP_404 = 404;

    HttpState(CODE code):_code(code){}
    
    std::string to_s() { return _states[_code]; }
private:
    CODE _code;
    static std:unordered_map<CODE,std::string> _states;
};