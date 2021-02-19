#include "UrlManager.h"
#include "../algorithm/algorithm.h"

UrlManager* UrlManager::instance = nullptr;

UrlManager::UrlManager()
:Array<HttpServer*>(2000){ }

UrlManager* UrlManager::getInstance(){
   if(instance == nullptr)instance = new UrlManager();
   return instance;
}

HttpServer *UrlManager::getServer(String str){
   int l = 0,r = m_size-1,mid;
   while(l<r){
      mid = (l+r+1)/2;
      if(m_data[mid]->getUrl()<str||m_data[mid]->getUrl()==str) l = mid;
      else r = mid-1;
   }
   if(m_data[l]->getUrl() == str)return m_data[l];
   return nullptr;
}