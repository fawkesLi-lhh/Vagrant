#include "HttpConnectManager.h"
#include "../config/Config.h"

HttpConnectManager::HttpConnectManager(int _max_user)
:tree(_max_user+100){ 
   tree.insert(HttpConnect());
}

bool HttpConnectManager::addHttpConnect(int sockfd,sockaddr_in address){
   return tree.insert(HttpConnect(sockfd,address));
}

void HttpConnectManager::removeHttpConnect(int sockfd,int epollfd){
   HttpConnect connect = tree.search(HttpConnect(sockfd,sockaddr_in()));
   connect.close_connect(epollfd);
   tree.remove(connect);
}

HttpConnect HttpConnectManager::getHttpConnect(int sockfd){
   return tree.search(HttpConnect(sockfd,sockaddr_in()));
}
