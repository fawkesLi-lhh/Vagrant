#ifndef _HTTPRESPONSE_H_
#define _HTTPRESPONSE_H_

#include "../algorithm/String.h"

class HttpResponse{
public:
   HttpResponse();
   String getHeader();
   String getValue();
   void addValue(const char* str);
   void addHeader(const char* str);
   void addCookie(const char* str);
   void addConnentLength(int length);
   void setResponseLength(int len);
   String& getResponse();
private:
   void generateResponse();
   String header,value;
   bool has_gen;
   int respLen;
};





#endif

