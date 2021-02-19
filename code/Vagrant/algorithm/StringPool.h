#ifndef _STRINGMANAGER_H_
#define _STRINGMANAGER_H_
#include <mutex>

#include "MemoryPool.h"

enum StringType{ CONST = 0,SHORT = 1,MIDDLE = 2,LONG = 3};
struct Block {
   char* m_data;
   int child;
   StringType type;
   Block(int len,StringType ty):m_data(new char[len]),child(1),type(ty){}
   Block(){}
};

class StringPool
{
public:
   static StringPool* getInstance();
   Block* malloc(StringType e);
   void free(Block* str);
   int getLength(StringType e);
   StringType getType(int len);

private:
   StringPool();
   static StringPool* instance;
   MemoryPool<Block> shortPool;
   MemoryPool<Block> middlePool;
   MemoryPool<Block> longPool;
   int shortLen;
   int middleLen;
   int longLen;
};




#endif
