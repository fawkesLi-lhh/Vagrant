#include"HttpRequest.h"

#include <cstring>

HttpRequest::HttpRequest(String s):httpMessage(s),message(s),
conntentLength(-1) {
   message.becomeFather();
   int now = 0,stap = 0;
   for(int i = 0;i<message.size();i++){
      if(message[i] == ' ' && stap == 0){
         message[i] = '\0';
         if(strcmp(message.c_str()+now,"GET") == 0) method = GET;
         else if(strcmp(message.c_str()+now,"POST") == 0) method = POST;
         else if(strcmp(message.c_str()+now,"HEAD") == 0) method = HEAD;
         else if(strcmp(message.c_str()+now,"PUT") == 0) method = PUT;
         else if(strcmp(message.c_str()+now,"DELETE") == 0) method = DELETE;
         else if(strcmp(message.c_str()+now,"TRACE") == 0) method = TRACE;
         else if(strcmp(message.c_str()+now,"OPTIONS") == 0) method = OPTIONS;
         else if(strcmp(message.c_str()+now,"CONNECT") == 0) method = CONNECT;
         else if(strcmp(message.c_str()+now,"PATCH") == 0) method = PATCH;
         else method = UNKOWN;
         stap++;
         now=i + 1;
      }
      else if(message[i] == ' ' &&stap == 1){
         message[i] = '\0';
         url.init(message,now);
         stap++;
         now=i + 1;
      }
      else if(message[i] == ' '||message[i] == '\n'){
         message[i] = '\0';
         httpProtocol.init(message,now);
         stap++;
         now=i + 1;
         break;
      }
   }
  
   for(int i = now;i<message.size();i++){
      if(message[i] == ':'){
         message[++i] ='\0';
         if(strcmp(message.c_str()+now,"Host:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            host.init(message,now);
            now = i+1;
         }
         else if(strcmp(message.c_str()+now,"Connection:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            connection.init(message,now);
            now = i+1;
         }
         else if(strcmp(message.c_str()+now,"Cookie:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            cookie.init(message,now);
            now = i+1;
         }
         else if(strcmp(message.c_str()+now,"Referer:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            referer.init(message,now);
            now = i+1;
         }
         else if(strcmp(message.c_str()+now,"Origin:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            origin.init(message,now);
            now = i+1;
         }
         else if(strcmp(message.c_str()+now,"Content-Length:") == 0){
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            sscanf(message.c_str()+now,"%d",&conntentLength);
            now = i+1;
         }
         else{
            now = i+1;
            while(message[++i]!='\n');
            message[i] = '\0';
            now = i+1;
         }
         if(message[i+1] == '\n') break;
      }
   }
   if(now == message.size())return;
   conntent.init(message,now+2);
   for(int i = now+1;i<message.size();i++){
      if(message[i] == '&'||message[i] == '='||message[i] == '\n'){
         message[i] = '\0';
      }
   }
}

String HttpRequest::getHttpMessage(){
   return httpMessage;
}

REQUEST_METHOD HttpRequest::getMethod(){
   return method;
}
String HttpRequest::getUrl(){
   return url;
}
String HttpRequest::getHttpProtocol(){
   return httpProtocol;
}

String HttpRequest::getHost(){
   return host;
}
String HttpRequest::getConnection(){
   return connection;
}
String HttpRequest::getCookie(){
   return cookie;
}
String HttpRequest::getReferer(){
   return referer;
}
String HttpRequest::getOrigin(){
   return origin;
}

String HttpRequest::getParameter(String name)const{
   String ans;
   int now = 0;
   for(int i = 0;i<=conntent.size();i++){
      if(conntent[i] == '\0'){
         if(strcmp(conntent.c_str()+now,name.c_str()) == 0){
            ans.init(conntent,i+1);
            return ans;
         }
         else {
            while(conntent[++i]!='\0'&&i<=conntent.size());
            now = i+1;
         }
      }
   }
   return String();
}


// GET /favicon.ico HTTP/1.1
// Host: localhost:6321
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
// Accept: image/webp,*/*
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Referer: http://localhost:6321/index.html
// Cookie: _ga=GA1.1.303439046.1606725789

// GET / HTTP/1.1
// Host: localhost:8652
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive
// Cookie: _ga=GA1.1.303439046.1606725789
// Upgrade-Insecure-Requests: 1

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

// POST /xinguan/ProvinceTotal HTTP/1.1// Host: localhost:6546// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0// Accept: application/json, text/javascript, */*; q=0.01// Accept-Language: en-US,en;q=0.5// Accept-Encoding: gzip, deflate// Content-Type: application/x-www-form-urlencoded; charset=UTF-8// Content-Length: 21// Origin: http://localhost:6321// Connection: keep-alive// Referer: http://localhost:6321/index.html// name=sda&passward=asd


