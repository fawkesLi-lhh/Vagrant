#ifndef _CONFIG_H_
#define _CONFIG_H_

class Config
{
public:
   static Config*getInstance();
   int getPort();
   int getMaxUser();
   char *getDataBaseUser();
   char *getDataBasePassward();
   char *getDataBaseName();
private:
   static Config* instance;
   Config();
private:
   int port;
   int max_user;
   char db_user[555];
   char db_passwd[555];
   char db_name[555];
};




#endif 
