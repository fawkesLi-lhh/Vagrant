#include "String.h"

#include <cstdio>

String nullString("NULL");

String::String(StringType ee) :e(ee),m_begin(0){
   if(e == CONST) {
      m_block = nullString.m_block;
      m_size = nullString.m_size;
      m_length = nullString.m_length;
      m_block->child++;
   }
   else {
      m_block = StringPool::getInstance()->malloc(e);
      m_length = StringPool::getInstance()->getLength(e);
      m_size = 0;
      m_block->m_data[0] = '\0';
   }
}

String::String(const char *str):String(StringPool::getInstance()->getType(strlen(str))) {
   if(m_block==nullptr)return;
   m_begin = 0;
   m_size = strlen(str);
   memcpy(m_block->m_data,str,m_size),m_length = m_size;
   m_block->m_data[m_size] = '\0';
}

String::String(const String& ss) { 
   m_begin = ss.m_begin;
   m_block = ss.m_block;
   m_size = ss.m_size;
   m_length = ss.m_length;
   e = CONST;
   m_block->child++;
}

String& String::operator=(const String& ss){
   destory(m_block);
   m_begin = ss.m_begin;
   m_block = ss.m_block;
   m_size = ss.m_size;
   m_length = ss.m_length;
   e = CONST;
   m_block->child++;
   return *this;
}


String::String(String&& ss) : String(ss.c_str()) { }

String::~String() {
   destory(m_block);
}

void String::destory(Block *block){
   block->child--;
   if(block->child<=0)StringPool::getInstance()->free(block);
}

bool String::init(const String &ss,int index){
   if(e !=CONST)return false;
   destory(m_block);
   m_begin = index+ss.m_begin;
   m_block = ss.m_block;
   m_size = ss.m_size-index;
   m_length = ss.m_length;
   m_block->child++;
   return true;
}

bool String::becomeFather(){
   e = StringPool::getInstance()->getType(m_length);
   Block *newBlock = StringPool::getInstance()->malloc(e);
   m_begin = 0;
   m_size = 0;
   Block *lastBlock = m_block;
   m_block = newBlock;
   if(lastBlock!=nullString.m_block)append(lastBlock->m_data+m_begin);
   m_begin = 0;
   destory(lastBlock);
}


char& String::operator[](int index)const{ 
   //index+m_begin>=m_size?m_block->m_data[0]:
   return m_block->m_data[index+m_begin];
}

bool String::operator==(const String &s)const{   return strcmp(s.c_str(),m_block->m_data+m_begin) == 0; }
bool String::operator<(const String &s)const{   return strcmp(m_block->m_data+m_begin,s.c_str())<0; }
int String::size()const{   return m_size;   }
void String::addSize(int len){ if(e == CONST) return; m_size+=len;m_block->m_data[m_size] = '\0'; }
int String::length(){   return m_length;   }
char *String::c_str() const {    return m_block->m_data+m_begin;   }
bool String::append(const String &str) { return append(str.c_str()); }
bool String::append(char c){ 
   if(e == CONST) return false;
   return m_size == m_length?false:(m_block->m_data[m_size++] = c,m_block->m_data[m_size] = '\0',true);
}
bool String::append(const char *str){
   if(e == CONST)  return false;
   if(m_size == m_length)return false;
   for(int i = 0;i<m_length-m_size;i++){
      if(str[i] == '\0'){
         m_size+=i;
         m_block->m_data[m_size] = '\0';
         return true;
      }
      m_block->m_data[i+m_size] = str[i];
   }
   m_size = m_length;
   m_block->m_data[m_size] = '\0';
   return false;
}
