#ifndef _NOTFIND_H_
#define _NOTFIND_H_

#include "../vagrant.h"

class HelloVagrant :public HttpServer
{
public:
   HelloVagrant();
   virtual bool doGet(HttpRequest &req,HttpResponse &resp);
};


#endif
