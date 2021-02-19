#ifndef _HTTPREQUEST_H_
#define _HTTPREQUEST_H_

#include "../algorithm/String.h"

enum REQUEST_METHOD { GET = 0,POST = 1,HEAD = 2,PUT,DELETE,TRACE,OPTIONS,CONNECT,PATCH, UNKOWN};

class HttpRequest{
public:
   HttpRequest(String s);
   
   String getHttpMessage();
   REQUEST_METHOD getMethod();
   String getUrl();
   String getHttpProtocol();
   String getHost();
   String getConnection();
   String getCookie();
   String getReferer();
   String getOrigin();
   String getParameter(String name) const;
private:
   String httpMessage;
   String message;

   REQUEST_METHOD method;
   int conntentLength;
   String url,httpProtocol;
   String host;
   String connection;
   String cookie;
   String referer;
   String origin;
   String conntent;
};

// POST /xinguan/ProvinceTotal HTTP/1.1
// Host: localhost:6546
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
// Accept: application/json, text/javascript, */*; q=0.01
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Content-Type: application/x-www-form-urlencoded; charset=UTF-8
// Content-Length: 28
// Origin: null
// Connection: keep-alive

// name=asdsda&passward=aasddas

// GET /favicon.ico HTTP/1.1
// Host: localhost:6321
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
// Accept: image/webp,*/*
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Referer: http://localhost:6321/index.html
// Cookie: _ga=GA1.1.303439046.1606725789

#endif



