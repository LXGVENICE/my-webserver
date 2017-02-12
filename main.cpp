#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <strings.h>
#include <sys/socket.h>


#include "HttpResponse.hpp"
#include "Util.hpp"

#define	IP "127.0.0.1"
#define	PORT 8080			/*  */
#define HTML "<html><body><h1>Hell World</h1></body></html>"

int main() {
  int listenFd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenFd == -1) {
    perror("socket failed");
    exit(1);
  }

  struct sockaddr_in listenAddr;
  bzero(&listenAddr, sizeof(listenAddr));
  listenAddr.sin_family = AF_INET;
  //set IP
  inet_pton(AF_INET,
            IP,
            &(listenAddr.sin_addr.s_addr));
  //set port short
  listenAddr.sin_port = htons(PORT);


  if (bind(listenFd,
           (struct sockaddr *) &listenAddr,
           sizeof(listenAddr))
      == -1)
  {
    perror("bind failed");
    exit(1);
  }
  printf("bind %s successed\n", IP);


  if (listen(listenFd, 5) == -1) {
    perror("listen failed");
    exit(1);
  }
  printf("listen %s:%d successed\n", IP, PORT);

  int clientFd = -1;
  std::string html(HTML);

  uint8_t buf[1024];
  while (1) {
    clientFd = accept(listenFd, NULL, 0);
    if (clientFd == -1) {
      perror("accept failed");
      exit(1);
    }


//HTTP/1.0 200 OK
//Content-Type: text/html
//Content-Length: 45
//Date: Wed, 08 Feb 2017 12:21:00 GMT

    printf("new connection is establish\n");

    std::string line;
    while (getLine(line, clientFd) != -1) {
      printf("%s\n", line.c_str());
    }

    //HttpRequest req();

    


    HttpResponse rep(200);
    rep.addHeader("Date", "Wed, 08 Feb 2017 12:21:00 GMT");
    rep.addHeader("Content-Type", "text/html");
    rep.addHeader("Content-Length", i2s(html.length()));
    rep.writeBody(html);


    std::string repMsg = rep.getPkg();
    printf("+++++++++++++++++\n");
    printf("%s", repMsg.c_str());
    printf("+++++++++++++++++\n");

//const char *html = "HTTP/1.1 200 OK\r\n"
//"Date: Sat, 11 Feb 2017 07:12:23 GMT\r\n"
//"Content-Type: text/html\r\n"
//"Content-Length: 5\r\n"
//"\r\n"
//"12345";


    int ret = send(clientFd, repMsg.data(), repMsg.length(), 0);
    if (ret == -1) {
      perror("send failed");
    }


    close(clientFd);
  }

}
