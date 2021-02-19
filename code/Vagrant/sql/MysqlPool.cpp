#include<thread>
#include<assert.h>

#include "MysqlPool.h"
#include "../config/Config.h"

MysqlPool* MysqlPool::instance = nullptr;

MysqlPool *MysqlPool::getInstance(){
   if(instance == nullptr)instance = new MysqlPool();
   return instance;
}

MysqlPool::MysqlPool():pool(::std::thread::hardware_concurrency(),false){
   for(int i = 0;i<::std::thread::hardware_concurrency();i++){
      MYSQL *sql = nullptr;
      sql = mysql_init(sql);
      if (!sql) assert(sql);
      Config*config = Config::getInstance();
      sql = mysql_real_connect(sql, "localhost",
                                 config->getDataBaseUser(), config->getDataBasePassward(),
                                 config->getDataBaseName(), 3306, NULL, 0);
      if (!sql) assert(sql);
      pool.free(sql);
   }
}

MYSQL* MysqlPool::get(){
   return pool.get();
}
void MysqlPool::free(MYSQL* m){
   pool.free(m);
}
