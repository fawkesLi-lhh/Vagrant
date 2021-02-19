#include"Config.h"

#include<fstream>
#include<string>
#include<thread>

Config* Config::instance = nullptr;

Config::Config(){
   std::ifstream fin("config.txt");
   std::string name;int val;
   fin>>name>>port;
   fin>>name>>max_user;
   fin>>name>>db_user;
   fin>>name>>db_passwd;
   fin>>name>>db_name;
   fin.close();
}

Config* Config::getInstance(){
   if(instance == nullptr) instance = new Config();
   return instance;
}

int Config::getPort(){
   return port;
}
int Config::getMaxUser(){
   return max_user;
}

char *Config::getDataBaseUser(){
   return db_user;
}
char *Config::getDataBasePassward(){
   return db_passwd;
}
char *Config::getDataBaseName(){
   return db_name;
}
