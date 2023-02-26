#include "Regul.h"


Regul::Regul(int in) : SocketClient(in){

}
void Regul::commande_chauffage(){
  std::string  cond;
  std::string buffer;
  std::vector<std::vector<std::string>> res;
  std::vector<std::vector<std::string>> res2;
  std::vector<std::vector<std::string>> res3;
  std::vector<std::vector<std::string>> res4;
  int seuilb,seuilh, temperature;

  res = requete->select("scenario","s1, seuil_h, seuil_b","");
  if(res[0][0] == "1"){
    res2 = requete->select("home", "temp_int","");
    res3 = requete->select("actionneur", "id_actionneur","type = 'chauf'");
    std::string::size_type size;
    seuilh = std::stoi(res[0][1], &size);
    seuilb = std::stoi(res[0][2], &size);
    temperature = std::stoi(res2[0][0], &size);
    if (res3.size() != 0) {
      std::cout << "/* message */" << '\n';
      std::cout << temperature << "---" << seuilb<< '\n';
      if(temperature < seuilb) {
        std::cout << "/* message */" << '\n';
        while(temperature < seuilh && res[0][0] == "1") {

          std::cout << "/* message */" << '\n';

          res4 = requete->select("home", "now() - date_temp","");
          std::string::size_type size;
          int num = std::stoi(res4[0][0], &size);
          // si le capteur de température intérieur n'a pas update depuis 5minute
          if(num == 300){
            requete->update("update scenario set s1 = '0'");
          }
          res = requete->select("scenario","s1, seuil_h, seuil_b","");
          std::cout << res3[0][0] << '\n';
          res2 = requete->select("home", "temp_int","");
          if (res4.size() != 0) {
            send_server(res3[0][0], "1");
          }
          temperature = std::stoi(res2[0][0], &size);
          sleep(10);
        }
        if (res3.size() != 0) {
          send_server(res3[0][0], "0");
        }
      }
    }
  }
}
void Regul::commande_allum2(){
  std::string  cond;
  std::string buffer;
  std::vector<std::vector<std::string>> res;
  std::vector<std::vector<std::string>> res2;
  std::vector<std::vector<std::string>> res3;
  std::vector<std::vector<std::string>> res4;
  res = requete->select("scenario","s2","");
  if (res[0][0] == "1") {
    res4 = requete2->select("actionneur", "id_actionneur","type = 'lum2'");
    res2 = requete2->select("scenario"," detec","");
    res3 = requete2->select("scenario","end_detec - now() ","");
    std::string::size_type size;
    int num = std::stoi(res3[0][0], &size);
    while (res2[0][0] == "1" && num > 0) {

      res2 = requete2->select("scenario"," detec","");
      res3 = requete2->select("scenario","end_detec - now() ","");
      num = std::stoi(res3[0][0], &size);
      std::cout << res4.size() << '\n';
      if (res4.size() != 0) {
        std::cout << "/* --------------------------- */" << '\n';
        send_server(res4[0][0], "1");
      }
      sleep(3);
    }
    if (res4.size() != 0) {
      send_server(res4[0][0], "0");
    }
  }
}
void Regul::commande_allum(){
  std::string  cond;
  std::string buffer;
  std::vector<std::vector<std::string>> res;
  std::vector<std::vector<std::string>> res2;
  std::vector<std::vector<std::string>> res3;
  std::vector<std::vector<std::string>> res4;
  int num;
  int num2;
  std::string::size_type size;
  res = requete3->select("scenario","s3","");

  if (res[0][0] == "1") {
    res4 = requete3->select("actionneur", "id_actionneur","type = 'lum1'");
    res2 = requete3->select("scenario","current_time() -  heure1","");
    res3 = requete3->select("scenario","heure2 - current_time()","");

    num = std::stoi(res2[0][0], &size);

    num2 = std::stoi(res3[0][0], &size);
    while (num > 0 && num2 > 0) {
      if (res4.size() != 0) {
        res2 = requete3->select("scenario","current_time() -  heure1","");
        res3 = requete3->select("scenario","heure2 - current_time()","");
        num = std::stoi(res2[0][0], &size);
        num2 = std::stoi(res3[0][0], &size);
        send_server(res4[0][0], "1");
      }
      sleep(3);
    }
    if (res4.size() != 0) {
      send_server(res4[0][0], "0");
    }
  }
}
