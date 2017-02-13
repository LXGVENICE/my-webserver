#program once
#include <unordered_map>
#include <string>
#include "HttpState.hpp"

class HttpResponse
{
public:
    HttpResponse(HttpState::CODE state):_state(state){}

    void addHeader(const std::string &key,const std::string &value)
    {
        _headers[key] = value;
    }

    void delHeader(const std::string &key)
    {
        _headers.erase(key);
    }

    void writeBody(const std::string &body)
    {
        _body = body;
    }

    std::string getPkg()
    {
        std::string pkg;
    }
private:
HttpState _state;
std::unordered_map<std::string,std::string> _headers;
std::string _body;
};