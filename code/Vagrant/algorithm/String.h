#ifndef _STRING_H_
#define _STRING_H_

#include<cstring>
#include"StringPool.h"

class String {
public:
   String(StringType ee = CONST);
   String(const char *str);
   String(const String& ss);
   String(String&& ss);
   ~String();
   bool init(const String &ss,int index = 0);
   bool becomeFather();
   String& operator=(const String& s);
   char& operator[](int index)const;
   bool operator==(const String &s)const;
   bool operator<(const String &s)const;
   int size()const;
   void addSize(int len);
   int length();
   char *c_str()const;
   bool append(const String &str) ;
   bool append(char c);
   bool append(const char *str);
private:
   void destory(Block *block);
private:
   Block *m_block;
   int m_begin;
   int m_size;
   int m_length;
   StringType e;
};

#endif