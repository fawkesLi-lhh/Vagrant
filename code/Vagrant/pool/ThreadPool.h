#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include"../algorithm/Queue.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <cstdio>

template<typename T>
class ThreadPool {
public:
   ThreadPool(int maxuser): attribute_(new Attribute(maxuser)){
      int threadCount = ::std::thread::hardware_concurrency();
      for(int i = 0; i < threadCount; i++) {
         ::std::thread([attribute = attribute_] {
            ::std::unique_lock<std::mutex> locker(attribute->mtx);
            while(true) {
               if(!attribute->workqueue.empty()) {
                  auto obj = attribute->workqueue.front();
                  attribute->workqueue.pop();
                  locker.unlock();
                  obj.process();
                  locker.lock();
               } 
               else if(attribute->isLive) break;
               else attribute->cond.wait(locker);
            }
         }).detach();
      }
   }
    
   ~ThreadPool() {
      if(static_cast<bool>(attribute_)) {
         {
            ::std::lock_guard<std::mutex> locker(attribute_->mtx);
            attribute_->isLive = true;
         }
         attribute_->cond.notify_all();
      }
   }

   bool append(T object) {
      bool flag = false;
      {
         ::std::lock_guard<std::mutex> locker(attribute_->mtx);
         flag = attribute_->workqueue.push(object);
      }
      attribute_->cond.notify_one();
      return flag;
   }

private:
   struct Attribute {
      ::std::mutex mtx;
      ::std::condition_variable cond;
      bool isLive;
      Queue<T> workqueue;
      Attribute(int maxlen):workqueue(maxlen),isLive(false){}
   };
   Attribute* attribute_;
};

#endif
