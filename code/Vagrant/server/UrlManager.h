#ifndef _URLMANAGER_H_
#define _URLMANAGER_H_

#include "../algorithm/Array.h"
#include "../http/HttpServer.h"

class UrlManager:private Array<HttpServer*>
{
private:
   static UrlManager* getInstance();
   static UrlManager* instance;
   UrlManager();
   HttpServer *getServer(String str);
   friend class Server;   
   friend class HttpConnect;
   friend int main();
};

#endif
