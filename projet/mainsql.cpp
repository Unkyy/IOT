
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;

int main(void)
{
	string host ="127.0.0.1";
	string login = "test";
	string pwd = "test";
	string nameBase = "mysql";


	MYSQL my;

	if(mysql_library_init(0,NULL, NULL)) {
		cerr << "echec de l'initialisation de la bibliotheque Mysql" << endl;
		exit(EXIT_FAILURE);
	}
	if(mysql_init(&my) == NULL) {
		cerr << "echec de l'initialisation du connecteur MySQL " << endl;
		exit(EXIT_FAILURE);
	}
	if(mysql_real_connect(&my, host.c_str(), login.c_str(), pwd.c_str(), nameBase.c_str(), 0, NULL, 0) == NULL) {
		cerr << "Echec de la connexion au serveur MySQL" << endl;
		mysql_close(&my);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}

	cout << "version mysql = " << mysql_get_server_info(&my) << endl;

	mysql_close(&my);
	mysql_library_end();
	exit(EXIT_SUCCESS);

}
