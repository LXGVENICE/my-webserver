#ifndef  HTTPSTATE_H
#define  HTTPSTATE_H
#include <unordered_map>

class HTTPState{
 public:
  typedef uint16_t CODE;

  static const CODE HTTP_200 = 200;
  static const CODE HTTP_404 = 404;

  HTTPState(CODE code) :
      _code(code)
  {}

  std::string to_s() {
    return _states[_code];
  }


 private:
  CODE _code;
  static std::unordered_map<CODE, std::string> _states;
};


#endif   /* ----- #ifndef HTTPSTATE_H ----- */
