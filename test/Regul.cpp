#include "Regul.h"


Regul::Regul(int in) : SocketClient(in){

}
void Regul::commande_chauffage(){
  std::string  cond;
  std::string buffer;
  std::vector<std::vector<std::string>> res;
  std::vector<std::vector<std::string>> res2;
  int seuilb,seuilh, temperature;

  //res = requete->select("scenario","s1, seuil_h, seuil_b","");
  if(res[0][0] == "1"){
    //res2 = requete->select("home", "temp_int","");
    std::string::size_type size;
    seuilh = std::stoi(res[0][1], &size);
    seuilb = std::stoi(res[0][2], &size);
    temperature = std::stoi(res2[0][0], &size);
    if (temperature < seuilb) {
      //send_server()
    }
    if (temperature > seuilh) {
      /* code */
    }
  }
}
void commande_allum(){
  std::string  cond;
  std::string buffer;
  std::vector<std::vector<std::string>> res;

  //res = requete->select("scenario","s2","");
  if(res[0][0] == "1"){

  }
}


bool Regul::time_range(int *time_sql){
   // current date/time based on current system
   time_t now = time(0);
   // cout << "Number of sec since January 1,1970:" << now << endl;
   tm *ltm = localtime(&now);
    // std::cout << time_sql[0] << "<"<< (int)ltm->tm_hour<< "<"<< time_sql[1] <<std::endl;
   if(time_sql[0] < (int)ltm->tm_hour && time_sql[1] > (int)ltm->tm_hour ){
     return true;
   }else{
     return false;
   }
}
