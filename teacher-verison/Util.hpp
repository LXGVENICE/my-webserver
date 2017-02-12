#ifndef  UTIL_H
#define  UTIL_H

#include <sstream>

std::string i2s(int num) {
  std::ostringstream os;
  os << num;
  return os.str();
}


int getLine(std::string &line/*out*/, int fd) {
  static char buf[1024];
  int headLen=0;

again:
    int ret = recv(fd, buf+headLen, 
                   sizeof(buf)-headLen, 0);
    if (ret == -1) {
      if (errno == EINTR) 
        goto again;

      perror("recv");
      return -1;
    }

    if (ret == 0) //connect closed by peer
      return -1;

    ret = 2;
    for (int i=ret-1; i != 0; --i) {
      if (buf[i] == '\n' && buf[i-1] == '\r')  {
        buf[i-1] = '\0';
        line = buf;
        printf("get a new line\n");
      }

      headLen = ret -i -1;
      memmove(buf, buf+i+1, headLen);
    }

    return 1;
}


#endif   /* ----- #ifndef UTIL_H ----- */
