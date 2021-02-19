#ifndef _HTTPCONNECT_H_
#define _HTTPCONNECT_H_

#include <netinet/in.h>

enum HttpConnectStatus { Read,Write,Wait };

class HttpConnect{
public:
   HttpConnect();
   HttpConnect(int sockfd,sockaddr_in address);
   void close_connect(int epollfd);
   void process();
   bool operator<(const HttpConnect & a);
   bool operator==(const HttpConnect & a);
public:
   HttpConnectStatus status;

private:
   bool read_event();
   bool write_event();

private:
   int m_sockfd;
   sockaddr_in m_address;
};

#endif
