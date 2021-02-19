#ifndef _MYSQLPOOL_H_
#define _MYSQLPOOL_H_

#include "../algorithm/MemoryPool.h"
#include <mysql/mysql.h>

class MysqlPool {
public:
   static MysqlPool *getInstance();

   MYSQL* get();
   void free(MYSQL* m);

private:
   MysqlPool();
   static MysqlPool* instance;
   MemoryPool<MYSQL> pool;
};




#endif
