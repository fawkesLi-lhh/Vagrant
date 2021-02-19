#include "Login.h"

#include <cstring>

bool Login::doPost(HttpRequest &req,HttpResponse &resp){
   MysqlRAII sql;
   char buffer[555];
   sprintf(buffer,"SELECT name,passwd,nick FROM user where name='%s'",req.getParameter(String("name")).c_str());
   if (mysql_query(sql.sql, buffer)) {
      printf("sql error\n");
      return true;
   }
   MYSQL_RES *result = mysql_store_result(sql.sql);
   int num_fields = mysql_num_fields(result);
   MYSQL_FIELD *fields = mysql_fetch_fields(result);
   while (MYSQL_ROW row = mysql_fetch_row(result)) {
      if(strcmp(row[1],req.getParameter(String("passward")).c_str()) == 0){
         sprintf(buffer,"{\n\"name\":\"%s\"\n}",row[2]);
         resp.addValue(buffer);
      }
      else{
         sprintf(buffer,"{\n\"name\":\"passwd error\"\n}");
         resp.addValue(buffer);
      }
   }
   mysql_free_result(result);

   return true;
}
