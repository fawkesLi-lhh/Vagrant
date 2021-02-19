#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>
#include <sys/uio.h>

#include <fstream>
#include <string>
#include <algorithm>

#include"Server.h"
#include"../config/Config.h"
#include "UrlManager.h"
#include "HelloVagrant.h"
#include "../sql/MysqlPool.h"

Server::Server():
threadpool(Config::getInstance()->getMaxUser()),
httpManager(Config::getInstance()->getMaxUser()),
epoller(Config::getInstance()->getMaxUser()) {
   initSocket(Config::getInstance()->getPort());
   epoller.addFd(listenFd, EPOLLIN | EPOLLET | EPOLLRDHUP);
   addUrl(new HelloVagrant());
}

void Server::loop(){
   printf("server begin\n");
   UrlManager* url = UrlManager::getInstance();
   AssetManager *assetManager = AssetManager::getInstance();
   //MysqlPool *mysqlPool = MysqlPool::getInstance();
   ::std::sort(&(url->operator[](0)),&(url->operator[](0))+url->size());
   while(true){
      int number = epoller.wait();
      for ( int i = 0; i < number; i++ ) {
         int sockfd = epoller.getEventFd(i);
         int event = epoller.getEvents(i);
         if(sockfd == listenFd){
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof( client_address );
            int connfd = accept( listenFd, ( struct sockaddr* )&client_address, &client_addrlength );
            if(connfd < 0 ){
               printf( "errno is: %d\n", errno );
               continue;
            }
            if(!httpManager.addHttpConnect(connfd,client_address)){
               /* log error */
            }
            epoller.addFd(connfd, EPOLLIN | EPOLLET | EPOLLRDHUP | EPOLLONESHOT);
         }
         else if(event & ( EPOLLRDHUP | EPOLLHUP | EPOLLERR ) ){
            httpManager.removeHttpConnect(sockfd,epoller.getEpollFd());
         }
         else if(event & EPOLLIN ){
            HttpConnect connect = httpManager.getHttpConnect(sockfd);
            connect.status = Read;
            int flag = threadpool.append(connect);
         }
         else if(event & EPOLLOUT){
            HttpConnect connect = httpManager.getHttpConnect(sockfd);
            connect.status = Write;
            threadpool.append(connect);
         }
      }
   }
}

void Server::initSocket(int port){
   int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
   assert( listenfd >= 0 );
   struct linger tmp = { 1, 0 };
   setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );

   int ret = 0;
   struct sockaddr_in address;
   bzero( &address, sizeof( address ) );
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = htonl(INADDR_ANY);
   address.sin_port = htons( port );

   ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
   assert( ret >= 0 );

   ret = listen( listenfd, 5 );
   assert( ret >= 0 );
   listenFd = listenfd;
}

void Server::addUrl(HttpServer* url){
   UrlManager *manager = UrlManager::getInstance();
   for(int i = 0;i<manager->size();i++){
      if(manager->operator[](i)->getUrl() == url->getUrl()){
         manager->operator[](i) = url;
         return;
      }
   }
   manager->push_back(url);
}