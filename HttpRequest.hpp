#ifndef  HTTPREQUEST_H
#define  HTTPREQUEST_H

enum HTTPMethod{
  GET, POST, DELETE, PUT, HEAD, 
  INVAILD;
}

class HttpRequest {
 public:


 private:
  HTTPMethod _method;
  std::unordered_map<std::string, std::string> _heads;

};

#endif   /* ----- #ifndef HTTPREQUEST_H ----- */
