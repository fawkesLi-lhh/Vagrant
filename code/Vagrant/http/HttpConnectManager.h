#ifndef _HTTPCONNECTMANAGER_H_
#define _HTTPCONNECTMANAGER_H_

#include <netinet/in.h>

#include "../algorithm/RBTree.h"
#include "HttpConnect.h"

class HttpConnectManager{
public:
   HttpConnectManager(int _max_user);
   bool addHttpConnect(int sockfd,sockaddr_in address);
   void removeHttpConnect(int sockfd,int epollfd);
   HttpConnect getHttpConnect(int sockfd);
private:
   RBTree<HttpConnect> tree;
};




#endif
