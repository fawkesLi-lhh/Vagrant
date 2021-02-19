#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"Array.h"

template<typename T>
class Queue : public Array<T>{
public:
   using Array<T>::m_size;
   using Array<T>::m_data;
   using Array<T>::m_length;
   Queue(int length) : Array<T>(length),beg(0),end(0){   }
   bool push(const T& t){
      if((end+1)%m_length == beg)return false;
      m_data[end++] = t;
      end%=m_length;
      return true;
   }
   bool empty(){
      return beg==end;
   }
   void pop(){
      if(beg!=end)beg++;
   }
   T front(){
      if(beg!=end)return m_data[beg];
      return T();
   }
private:
   int beg,end;
};

#endif