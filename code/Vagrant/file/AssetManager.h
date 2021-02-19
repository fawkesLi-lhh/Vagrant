#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "../algorithm/String.h"
#include "../algorithm/Array.h"

struct File {
   char *data;
   int len;
};

class AssetManager {
public:
   static AssetManager* getInstance();
   File getFile(String name);
private:
   void ReadDir(char * path);
   AssetManager();
   Array<String> fileNameArray;
   Array<File> fileArray;
   static AssetManager* instance;
   friend int main();
};




#endif
