#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "AssetManager.h"
#include "../algorithm/algorithm.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager():fileNameArray(1111),fileArray(111){
   char path[1111] = "asset";
   ReadDir(path);
   ::std::sort(&fileNameArray[0],&fileNameArray[0]+fileNameArray.size());
   struct stat file_stat;
   for(int i = 0;i<fileNameArray.size();i++){
      path[5] = '\0';
      strcat(path,fileNameArray[i].c_str());
      stat(path,&file_stat);
      int fd = open(path,O_RDONLY);
      char* data = (char *)mmap(0,file_stat.st_size,PROT_READ,MAP_PRIVATE,fd,0);
      int len = file_stat.st_size;
      fileArray.push_back({data,len});
   }
}

AssetManager* AssetManager::getInstance(){
   if(instance == nullptr)instance = new AssetManager();
   return instance;
}

void AssetManager::ReadDir(char *path){
   DIR *dir; dirent *ptr;int len = strlen(path);
   if ((dir=opendir(path)) == NULL){
      perror("Open dir error...");
      exit(1);
   }
   while ((ptr=readdir(dir)) != NULL){
      if(ptr->d_name[0] == '.') continue;
      strcat(path,"/");
      strcat(path,ptr->d_name);
      if(ptr->d_type == 8) fileNameArray.push_back(String(path+5));
      if(ptr->d_type == 4) ReadDir(path);
      path[len] = '\0';
   }
   closedir(dir);
}

File AssetManager::getFile(String name){
   int index = binary_search(&fileNameArray[0],&fileNameArray[0]+fileNameArray.size(),name)-&fileNameArray[0];
   if(name == fileNameArray[index]) return fileArray[index];
   return {nullptr,0};
}