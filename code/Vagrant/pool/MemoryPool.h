#ifndef _MEMORYPOOL_H_
#define _MEMORYPOOL_H_

#include"../algorithm/Stack.h"

/*
Classes that use MemoryPool must have an argumentless constructor and an init() function
*/

template<typename T>
class MemoryPool{
public:
   MemoryPool(int length,bool flag = true) : stack(length),data(length){
      if(flag){
         for(int i = 0;i<length;i++)
         stack.push(new T()),data.push(stack.top());
      }
   }
   ~MemoryPool(){ for(int i = 0;i<data.size();i++){ delete data[i];}}
   int length(){return data.length();}
   void free(T *obj){   stack.push(obj);}
      T *get(){
      if(stack.empty())return nullptr;
      return stack.pop();
   }
private:
   Stack<T*> stack;
   Stack<T*> data;
};

#endif
