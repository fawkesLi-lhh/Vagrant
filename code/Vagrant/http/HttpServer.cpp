#include"HttpServer.h"

HttpServer::HttpServer(String url)
: m_url(url) { }

String HttpServer::getUrl(){
   return m_url;
}

bool HttpServer::doGet(HttpRequest &req,HttpResponse &resp){ return false; }
bool HttpServer::doPost(HttpRequest &req,HttpResponse &resp){ return false; }