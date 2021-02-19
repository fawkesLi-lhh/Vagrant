#ifndef _LOHIN_H_
#define _LOHIN_H_
#include "../Vagrant/vagrant.h"

class Login :public HttpServer
{
public:
   Login():HttpServer("/login"){}
   virtual bool doPost(HttpRequest &req,HttpResponse &reps);
};



#endif
