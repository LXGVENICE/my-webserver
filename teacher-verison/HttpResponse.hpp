#include <unordered_map>
#include <string>
#include "HttpState.hpp"




class HttpResponse {
 public:
  HttpResponse(HTTPState::CODE state) 
      :_state(state)
  {}

  void addHeader(const std::string &key, const std::string &value)
  {
    _headers[key] = value;
  }
  void delHeader(const std::string &key)
  {
    _headers.erase(key);
  }

  //void writeBody(uint8_t *buf, size_t bufLen) {
  //}

  void writeBody(const std::string & body) {
    _body = body;
  }

  std::string getPkg() {
    std::string pkg;

#define	CRFL "\r\n"
    //HTTP/1.1. 200 OK
    pkg.append("HTTP/1.0 ");
    pkg.append(_state.to_s());
    pkg.append(CRFL); //FIXME use CRFL 

    for (auto e : _headers) {
      //Key : Value
      pkg.append(e.first);
      pkg.append(": ");
      pkg.append(e.second);
      pkg.append(CRFL);
    }

    pkg.append(CRFL);
    pkg.append(_body);

    return pkg;
  }


 private:
  //static char * const CRFL = "/r/n";
  HTTPState _state;
  std::unordered_map<std::string, std::string> _headers;;

  std::string _body;

};
