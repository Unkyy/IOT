#ifndef REQSQL_H
#define REQSQL_H

#include <iostream>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <mysql/mysql.h>
#include <vector>

#include "Bdd.h"

class ReqSql {
	public:
	ReqSql();
	void update(std::string sql);
	std::vector<std::vector<std::string>> select(std::string table, std::string champ,std::string condition);
	void insert(std::string mot);

	private:
	MYSQL sql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::string * tabLog ;

};

#endif
