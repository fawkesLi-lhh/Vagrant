#include "MysqlPool.h"

class MysqlRAII {
public:
   MysqlRAII():sql(nullptr){
      MysqlPool* pool = MysqlPool::getInstance();
      sql = pool->get();
   }
   ~MysqlRAII(){MysqlPool::getInstance()->free(sql);}
   MYSQL *sql;
};

