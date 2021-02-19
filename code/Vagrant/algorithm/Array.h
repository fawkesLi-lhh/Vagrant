#ifndef _ARRAY_H_
#define _ARRAY_H_

template<typename T>
class Array {
public:
   Array(int length) : m_data(new T[length+5]), m_size(0),m_length(length){   }
   virtual ~Array(){delete[]m_data;}
   int length(){return m_length;}
   int size(){return m_size;}
   T &operator[](int index){return m_data[index];}
   void push_back(T t){ m_data[m_size++] = t; }
protected:
   T *m_data;
   int m_size;
   int m_length;
};

#endif