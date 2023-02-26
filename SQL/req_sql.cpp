#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <mysql/mysql.h>
#include "req_sql.h"
using namespace std;

req_sql::req_sql(string  in_host, string  in_login, string  in_pwd, string  in_nameDataBase){
	host = in_host;
	login = in_login;
	pwd = in_pwd;
	nameData = in_nameDataBase;

	cout << " connection à la base de donnée"<< nameData << endl;

	

	if(mysql_library_init(0,NULL,NULL)){
		cerr << "echec de l'initialisation de la bibliotheque Mysql" << endl;
		exit(EXIT_FAILURE);
	}
	if(mysql_init(&sql) == NULL) {
		cerr << "echec de l'initialisation du connecteur MySQL" << endl;
		exit(EXIT_FAILURE);
	}
	if(mysql_real_connect(&sql, host.c_str(), login.c_str(),pwd.c_str(),nameData.c_str(), 0,NULL,0) == NULL) {
		cerr << "Echec de la connexion au serveur MySQL" << endl;
		mysql_close(&sql);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}
	if (mysql_select_db(&sql, nameData.c_str()) != 0) {
		cerr << "Echec de la selection de la BD " << nameData << endl;
		cerr << mysql_error(&sql) << endl;
		mysql_close(&sql);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}
}

void req_sql::select(string table, string champ){

	string mot = "SELECT " + champ + " FROM " + table;
	

	//cout << mot <<endl; 
	    if (mysql_query(&sql, mot.c_str()) != 0) {
		    cerr << "Echec de la requete" << endl;
		    cerr << mysql_error(&sql) << endl;
		    mysql_close(&sql);
		    mysql_library_end();
		    exit(EXIT_FAILURE);
	    }
	    res = mysql_use_result(&sql);
	    if (res == NULL)
	    {
		    cerr << "Echec de la recuperation des resultats" << endl;
	            cerr << mysql_error(&sql) << endl;  
	    	    mysql_close(&sql);
		    mysql_library_end();
		    exit(EXIT_FAILURE);                            
	    }

	    cout << "+---------------+" << endl;
            while ((row = mysql_fetch_row(res)) != NULL) {
		  
		    cout << row[0] << " - " << row[1] << " - " << row[2] << endl;
	    }
	    mysql_free_result(res);
}

void req_sql::update(string table, string value, int id_capteur){
	
	char tampon[10];
	sprintf (tampon, "%d", id_capteur) ;	

	string mot = "UPDATE " + table + "SET value = '" + value + "' WHERE id_capteur = " + tampon;
	
	cout << mot << endl;


	//if(mysql_query(&sql, 


}
