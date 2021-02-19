#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

template<typename T>
T *binary_search(T* l,T* r,T x){
   r--;
   while(l<r){
      T* mid = l+(r-l+1)/2;
      if(*mid<x || *mid==x) l = mid;
      else r = mid-1;
   }
   return l;
}

#endif
