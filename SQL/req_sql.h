#include <iostream>
#include <mysql/mysql.h>

using namespace std;
class req_sql {
	public:
	req_sql(string host, string login, string pwd, string  nameDataBase);
	void update(string table,string value, int id_capteur);
	void select(string table, string champ = "*");
	private:
	MYSQL sql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	string host,login,pwd,nameData;

};
