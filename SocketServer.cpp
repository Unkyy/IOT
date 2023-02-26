#include "SocketServer.h"

SocketServer::SocketServer(int port)
{
    mastersocket = socket(AF_INET , SOCK_STREAM , 0);
    if(mastersocket == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    puts("Socket created");

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

}
void SocketServer::listen_server(){

  if(bind (mastersocket, (sockaddr *) &sin, sizeof sin) == SOCKET_ERROR)
  {
      perror("bind()");
      exit(errno);
  }

  puts("bind done");

  if(listen(mastersocket, nb_user) == SOCKET_ERROR)
  {
      perror("listen()");
      exit(errno);
  }

  puts("Listenincg");
}

int SocketServer::AcceptClient(){
  sockaddr_in csin = { 0 };
  unsigned int sinsize = sizeof csin;

  int new_socket =   accept(mastersocket, (struct sockaddr *)&csin, &sinsize);

  puts("client");
  return new_socket;
}

void SocketServer::client(int sock,SocketClient *commande) {
    std::string buffer;

    if(sock == SOCKET_ERROR)
      {
        perror("send()");
        exit(errno);
      }

      buffer = " Serveur connecté \r";
      if(send(sock, buffer.c_str(), buffer.length(), 0) == SOCKET_ERROR)
      {
        perror("send()");
        exit(errno);
      }

}

void SocketServer::Tram_client(int sock,SocketClient *commande){
  std::string buffer;
  //std::cout << "tram reçu:" << tram_recu << "tram match: " << tram_match <<'\n';
  nb_octet = recv(sock, msg, taille_max -1, 0);
  //tram_recu += 1;
  //std::cout << msg << '\n';
  Xml_Send_bdd(msg,commande,sock);
}
void SocketServer::Xml_Send_bdd(std::string str,SocketClient *commande,int sock){
      std::regex valueRegex("<([a-zA-Z|_]*)><[a-z0-9|_|.]*>([0-9|.]*)</[a-z|_]*><?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*>?<?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*>?<?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*>?<?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*></[a-zA-Z|_]*>");
    //std::regex commandeRegex("<([a-zA-Z|_]*)><[a-z|_]*>([0-9]*)<\/[a-z|_]*><([a-z|_]*)>([a-z0-9|_|.]*)<\/[a-zA-Z|_]*><\/[a-zA-Z|_]*>");


    std::smatch res;
    int conf1 = 5;
    int conf2 = 6;
    int regex = 4;

    std::string config[conf1][conf2] = {
      {"pluvio", "taux_pluie", "total_pluie","null","null","date_pluie"},
      {"cons", "consommation_1", "consommation_2","consommation_3","total_elec","date_elec"},
      {"temp", "temp_int", "hum_int","null","null", "date_temp"},
      {"tempEx", "temp_ext", "hum_ext","null","null", "date_temp_ex"},
      {"vent", "direction", "rafale", "vitesse","null","date_vent"}
    };

    std::string scenario[3][2] = {
      {"s1", "chauf"},
      {"s2", "lum1"},
      {"s3", "lum2"},
    };

    //string str = "<temp><id_capteur>78</id_capteur><float>"+ temp +"</float><float>20.0</float></temp>";
    //string str = "<commande><id>1000</id><bool>1</bool></commande>";
    //string str = "<actionneur><id>1000</id></actionneur>";


    std::string::const_iterator searchStart2(str.cbegin());
    for (int i = 0; regex_search( searchStart2, str.cend(), res, valueRegex);i++ )
    {
        tram_match += 1;
        std::cout << res[0] <<   '\n';

        if (res[1] == "commande") {
          cond = "id_actionneur = " + res[2].str();
          ResSql = requete->select("actionneur","type",cond);
          for (int i = 0; i < 3; i++) {
            if (ResSql[0][0] == scenario[i][1]) {
              requete->update("update scenario set "+ scenario[i][0] +" = '0'");
            }
          }
          commande->send_server(res[2].str(), res[4].str());
        }else{

          cond = "id_capteur = " + res[2].str();
          ResSql = requete->select("capteur","pos",cond);
          if(ResSql.size() != 0){
            if (res[1] == "detect") {
              ResSql = requete->select("scenario", "duree", "");
              std::string duree = "now() + " + ResSql[0][0];

              requete->update("update scenario set detec = '1', end_detec = "+ duree + " where id = 1");
            }
            else if (res[1] == "temp") {
                if(ResSql[0][0] == "int"){
                  ResSql = requete->select("home","now() - date_temp","");
                  std::string::size_type size;
                  int num = std::stoi(ResSql[0][0], &size);
                  //std::cout<<"s bdd: " << num << '\n';
                  if (num > 30) {
                    req = "UPDATE home SET ";
                    for (int l = 1; l < conf2; l++) {
                      if (config[2][l] != "null") {
                        req += config[2][l];
                        req += " = ";
                        if (res[regex] != "") {
                          req +=  res[regex];
                        }
                        if (config[2][l] != "date_temp") {
                          req += ", ";
                        }else {
                          req += "NOW()";
                        }
                        regex += 2;
                      }
                    }
                    requete->update(req);
                  }
                }else{
                  ResSql = requete->select("home","now() - date_temp_ex","");
                  std::string::size_type size;
                  int num = std::stoi(ResSql[0][0], &size);
                //  std::cout<<"s bdd: " << num << '\n';
                  if (num > 30) {
                  req = "UPDATE home SET ";
                  for (int l = 1; l < conf2; l++) {
                    if (config[3][l] != "null") {
                      req += config[3][l];
                      req += " = ";
                      if (res[regex] != "") {
                        req +=  res[regex];
                      }
                      //std::cout << config[3][l] << '\n';
                      if (config[3][l] != "date_temp_ex") {
                        req += ", ";
                      }else {
                        req += "NOW()";
                      }
                      regex += 2;
                    }
                  }
                  requete->update(req);
                }
                }
              }else{

                  for (int l = 0; l < conf1; l++) {
                      //std::cout << res[1] <<"=="<< config[l][0]<< '\n';
                      if (res[1] == config[l][0]) {
                        //std::cout << config[l][2] << config[l][3] << config[l][4] << '\n';
                      //  std::cout << "/* message */" << '\n';
                        std::string datesql = "now() - " + config[l][5];//date"
                        ResSql = requete->select("home",datesql,"");
                        std::string::size_type size;
                        int num = std::stoi(ResSql[0][0], &size);
                        //std::cout <<"s bdd: " << num << '\n';
                        if (num > 30) {
                          req = "UPDATE home SET ";
                          for (int x = 1; x < conf2; x++) {

                            if (config[l][x] != "null") {
                              req += config[l][x];
                              req += " = ";
                              if (res[regex] != "") {
                                req +=  res[regex];
                              }
                              std::cout << config[l][x]  << '\n';
                              if (config[l][x] == "date_vent"|| config[l][x] == "date_elec"||config[l][x] == "date_pluie") {
                                req += "NOW()";
                              }else {
                                req += ", ";
                              }
                              regex += 2;
                            }
                          }
                      requete->update(req);
                      }
                    }
                  }
              }
          }
        }
      searchStart2 = res.suffix().first;
    }
}

SocketServer::~SocketServer()
{
    closesocket(mastersocket);
}
