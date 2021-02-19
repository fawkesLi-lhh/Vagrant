#include "StringPool.h"

#include <thread>

StringPool::StringPool()
:shortPool(::std::thread::hardware_concurrency()*600,false),
middlePool(::std::thread::hardware_concurrency()*60,false),
longPool(::std::thread::hardware_concurrency()*6,false),
shortLen(20),middleLen(200),longLen(2000){  
   for(int i = 0;i<shortPool.length();i++) shortPool.free(new Block(shortLen+50,SHORT));
   for(int i = 0;i<middlePool.length();i++) middlePool.free(new Block(middleLen+50,MIDDLE));
   for(int i = 0;i<longPool.length();i++) longPool.free(new Block(longLen+50,LONG));
}

StringPool* StringPool::instance = nullptr;

StringPool* StringPool::getInstance(){
   if(instance == nullptr)instance = new StringPool();
   return instance;
}

Block* StringPool::malloc(StringType e){
   Block* ans = nullptr;
   if(e == SHORT)ans = shortPool.get();
   if(e == MIDDLE)ans = middlePool.get();
   if(e == LONG)ans = longPool.get();
   ans->child = 1;
   return ans;
}
void StringPool::free(Block* block){
   if(block == nullptr) return;
   if(block->type == SHORT) shortPool.free(block);
   if(block->type == MIDDLE) middlePool.free(block);
   if(block->type == LONG) longPool.free(block);
}

int StringPool::getLength(StringType e){
   if(e == SHORT)return shortLen;
   if(e == MIDDLE)return middleLen;
   if(e == LONG)return longLen;
   return 0;
}

StringType StringPool::getType(int len){
   if(len<=shortLen) return SHORT;
   if(len<=middleLen) return MIDDLE;
   if(len<=longLen) return LONG;
   return CONST;
}
