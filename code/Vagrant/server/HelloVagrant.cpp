#include "HelloVagrant.h"

HelloVagrant::HelloVagrant()
: HttpServer("/"){ }

bool HelloVagrant::doGet(HttpRequest &req,HttpResponse &resp){
   resp.addValue("HelloVagrant");

   return true;
}
