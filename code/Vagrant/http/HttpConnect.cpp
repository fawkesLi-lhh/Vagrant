#include <sys/uio.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>
#include <cstdio>
#include <sys/uio.h>

#include "HttpConnect.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "../server/UrlManager.h"
#include"../algorithm/String.h"
#include "../file/AssetManager.h"

HttpConnect::HttpConnect(){}

HttpConnect::HttpConnect(int sockfd,sockaddr_in address){
   status = Wait;
   m_sockfd = sockfd;
   m_address = address;
   int error = 0;
   socklen_t len = sizeof( error );
   getsockopt( m_sockfd, SOL_SOCKET, SO_ERROR, &error, &len );
   int reuse = 1;
   setsockopt( m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof( reuse ) );
}

void HttpConnect::close_connect(int epollfd){
   epoll_ctl( epollfd, EPOLL_CTL_DEL, m_sockfd, 0 );
   close(m_sockfd);
}

void HttpConnect::process(){
   if(status == Read) {
      read_event();
      status = Write;
   }
   else if( status == Write){
      write_event();
      status = Wait;
   }
}

bool HttpConnect::read_event(){
   String str(LONG);
   int read_bytes = 0;
   while(true){
      read_bytes = recv(m_sockfd,str.c_str()+str.size(),str.length()-str.size(),0);
      if(read_bytes == -1){
         if(errno == EAGAIN || errno == EWOULDBLOCK)break;
         return false;
      }
      else if(read_bytes == 0) return false;
      str.addSize(read_bytes);
   }
   //printf("%s\n",str.c_str());
   HttpRequest req(str);
   //  printf("%s\n",req.getParameter(String("name")).c_str());
   //  printf("%s\n",req.getParameter(String("passward")).c_str());
   HttpResponse resp;

   AssetManager *assetManager = AssetManager::getInstance();
   File file = assetManager->getFile(req.getUrl());
   if(file.len!=0){
      struct iovec iv[2];
      int iv_len = 2;
      resp.setResponseLength(file.len);
      iv[0].iov_base = resp.getResponse().c_str();
      iv[0].iov_len = resp.getResponse().size();
      iv[1].iov_base = file.data;
      iv[1].iov_len = file.len;
      writev(m_sockfd,iv,iv_len);
   }
   else {
      UrlManager *manager = UrlManager::getInstance();
      HttpServer *server = manager->getServer(req.getUrl());
      if(server!=nullptr){
         if(server->doGet(req,resp));
         else(server->doPost(req,resp));
      }
      write(m_sockfd,resp.getResponse().c_str(),resp.getResponse().size());
   }
   
   return true;
}
bool HttpConnect::write_event(){

}

bool HttpConnect::operator<(const HttpConnect & a){
   return m_sockfd<a.m_sockfd;
}

bool HttpConnect::operator==(const HttpConnect & a){
   return m_sockfd == a.m_sockfd;
}
