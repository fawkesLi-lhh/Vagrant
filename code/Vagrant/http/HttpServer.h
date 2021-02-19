#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include"../algorithm/String.h"
#include"HttpRequest.h"
#include"HttpResponse.h"

/*
Don't declare member variables in subclasses of this class,
Otherwise,there will be unpredictable errors
*/

class HttpServer{
public:
   HttpServer(String url);
   virtual bool doGet(HttpRequest &req,HttpResponse &resp);
   virtual bool doPost(HttpRequest &req,HttpResponse &resp);
   String getUrl();
private:
   String m_url;
};

#endif