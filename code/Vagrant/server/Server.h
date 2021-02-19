#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/epoll.h> 
#include <fcntl.h>  
#include <unistd.h> 
#include <assert.h>
#include <errno.h>

#include "Epoller.h"
#include "../pool/ThreadPool.h"
#include "../http/HttpConnectManager.h"
#include "../http/HttpServer.h"

class Server
{
public:
   Server();

   void loop();

   void addUrl(HttpServer* url);

private:
   void initSocket(int port);
private:
   ThreadPool<HttpConnect> threadpool;
   HttpConnectManager httpManager;
   Epoller epoller;
   int listenFd;
};


#endif
