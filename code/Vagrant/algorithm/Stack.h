#ifndef _STRACK_H_
#define _STRACK_H_

#include"Array.h"

template<typename T>
class Stack : public Array<T>{
public:
   using Array<T>::m_size;
   using Array<T>::m_data;
   using Array<T>::m_length;
   Stack(int length) : Array<T>(length){   }
   bool empty(){ return m_size == 0; }
   T top(){ return m_data[m_size-1]; }
   T pop(){   return m_data[--m_size]; }
   bool push(T obj){
      if(m_size+1>=m_length)return false;
      m_data[m_size++] = obj;
      return true;
   }
   T operator[](int index) {
      return m_data[index];
   }
   int size() {
      return m_size;
   }
};

#endif
