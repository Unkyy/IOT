#include "ReqSql.h"


ReqSql::ReqSql(){
	Bdd login;
	tabLog = login.getlogin();

	// host = tabLog[0];
	// login = tabLog[1];
	// pwd = tabLog[2];
	// nameData = tabLog[3];

	std::cout << " connection à la base de donnée "<< tabLog[3] << std::endl;


	if(mysql_library_init(0,NULL,NULL)){
		std::cerr << "echec de l'initialisation de la bibliotheque Mysql" << std::endl;
		exit(EXIT_FAILURE);
	}
	if(mysql_init(&sql) == NULL) {
		std::cerr << "echec de l'initialisation du connecteur MySQL" << std::endl;
		exit(EXIT_FAILURE);
	}
	if(mysql_real_connect(&sql, tabLog[0].c_str(), tabLog[1].c_str(),tabLog[2].c_str(),tabLog[3].c_str(), 0,NULL,0) == NULL) {
		std::cerr << "Echec de la connexion au serveur MySQL" << std::endl;
		mysql_close(&sql);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}
	if (mysql_select_db(&sql, tabLog[3].c_str()) != 0) {
		std::cerr << "Echec de la selection de la BD " << tabLog[3]  << std::endl;
		std::cerr << mysql_error(&sql) << std::endl;
		mysql_close(&sql);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}
}

std::vector<std::vector<std::string>> ReqSql::select(std::string table, std::string champ, std::string condition){

	std::string mot = "SELECT " + champ + " FROM " + table;
	std::vector<std::vector<std::string>> res_requete;
	if (condition != "") {
		mot =  mot + " where " + condition;
	}
	std::cout << mot <<std::endl;

	    if (mysql_query(&sql, mot.c_str()) != 0) {
		    std::cerr << mysql_error(&sql) << std::endl;
		    mysql_close(&sql);
		    mysql_library_end();
		    exit(EXIT_FAILURE);
	    }

	    res = mysql_use_result(&sql);

	    if (res == NULL)
	    {
		    std::cerr << "Echec de la recuperation des resultats" << std::endl;
	      std::cerr << mysql_error(&sql) << std::endl;
	      mysql_close(&sql);
		    mysql_library_end();
		    exit(EXIT_FAILURE);
	    }
			int col =  mysql_num_fields(res);
	    //std::cout << "+---------------+" << std::endl;
      for (int i=0; (row = mysql_fetch_row(res)) != NULL; i++) {
				res_requete.push_back(std::vector<std::string>());
				 for (int l = 0; l < col; l++) {
					 res_requete[i].push_back(row[l]);
				 }

	    }

	    mysql_free_result(res);
			return res_requete;
}

void ReqSql::update(std::string mot){

	std::cout << mot << std::endl;
	if (mysql_query(&sql, mot.c_str()) != 0) {
		std::cerr << "Echec de la requete" << std::endl;
		std::cerr << mysql_error(&sql) << std::endl;
		mysql_close(&sql);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}
}

void ReqSql:: insert(std::string mot){
	std::cout << mot << std::endl;
	if (mysql_query(&sql, mot.c_str()) != 0) {
		std::cerr << "Echec de la requete" << std::endl;
		std::cerr << mysql_error(&sql) << std::endl;
		mysql_close(&sql);
		mysql_library_end();
		exit(EXIT_FAILURE);
	}
}

// void ReqSql::select(std::string table,std::string id_capteur, std::string value){
//
// 	std::string mot = "UPDATE " + table + " SET value = '" + value + "' WHERE id_capteur = " + id_capteur;
// 	std::cout << mot << std::endl;
//
// 	if (mysql_query(&sql, mot.c_str()) != 0) {
// 		std::cerr << "Echec de la requete" << std::endl;
// 		std::cerr << mysql_error(&sql) << std::endl;
// 		mysql_close(&sql);
// 		mysql_library_end();
// 		exit(EXIT_FAILURE);
// 	}
// }
