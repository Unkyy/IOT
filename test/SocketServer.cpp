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
    std::cout<< "la socket:" << sock << '\n';

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

  nb_octet = recv(sock, msg, taille_max -1, 0);

  Xml_Send_bdd(msg,commande,sock);
}
void SocketServer::Xml_Send_bdd(std::string str,SocketClient *commande,int sock){
    std::regex valueRegex("<([a-zA-Z|_]*)><[a-z|_]*>([0-9]*)</[a-z|_]*><?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*>?<?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*>?<?([a-z|_]*)>?([a-z0-9|_|.]*)<?/?[a-zA-Z|_]*>?</[a-zA-Z|_]*>");
    //std::regex commandeRegex("<([a-zA-Z|_]*)><[a-z|_]*>([0-9]*)<\/[a-z|_]*><([a-z|_]*)>([a-z0-9|_|.]*)<\/[a-zA-Z|_]*><\/[a-zA-Z|_]*>");

    std::smatch res;
    int conf1 = 6;
    int conf2 = 5;
    int regex = 4;

    std::string config[conf1][conf2] = {
      {"pluvio", "taux_pluie", "total_pluie","date_pluie","null"},
      {"cons", "consomation_1", "consomation_2","consomation_3","date_elec"},
      {"temp", "temp_int", "hum_int","date_temp", "null"},
      {"tempEx", "temp_ext", "hum_ext","date_temp_ex", "null"},
      {"vent", "direction", "rafale", "vitesse","date_vent"},
      {"detect", "actif", "null","null","null"}
    };

    // {"pluvio", "total_pluie", "taux_pluie","null"},
    //       {"cons", "consomation_1", "consomation_2","consomation_3" "date_eleec"},
    //       {"tempI", "temp_int", "hum_int","null""date_temp"},
    //       {"tempE", "temp_ext", "hum_int","null""date_temp_ex"},
    //       {"vent", "direction", "rafale", "vitesse""date_vent"},

    //string str = "<temp><id_capteur>78</id_capteur><float>"+ temp +"</float><float>20.0</float></temp>";
    //string str = "<commande><id>3</id><bool>false</bool></commande>";
    //string str = "<actionneur><id>1000</id></actionneur>";

    // std::string::const_iterator searchStart( str.cbegin() );
    // for (int i = 0; regex_search(searchStart, str.cend(), res, commandeRegex);i++ )
    // {
    //     commande->send_server(res[2].str(), res[4].str());
    //
    //   searchStart = res.suffix().first;
    // }

    std::string::const_iterator searchStart2(str.cbegin());
    for (int i = 0; regex_search( searchStart2, str.cend(), res, valueRegex);i++ )
    {
        std::cout << res[0] <<   '\n';
        if (res[1] == "commande") {

          commande->send_server(res[2].str(), res[4].str());

        }else{
          cond = "id_capteur = " + res[2].str();
          ResSql = requete->select("capteur","type, pos",cond);
          if(ResSql.size() != 0){
            if (ResSql[0][0] == res[1]) {
              if (res[1] == "temp") {
                if(ResSql[0][1] == "int"){
                  ResSql = requete->select("home","now() - date_temp","");
                  std::string::size_type size;
                  int num = std::stoi(ResSql[0][0], &size);
                  std::cout << num << '\n';
                  if (num > 30) {
                    req = "UPDATE home SET ";
                    for (int l = 1; l < conf2; l++) {
                      if (config[2][l] != "null") {
                        req += config[2][l];
                        req += " = ";
                        if (res[regex] != "") {
                          req +=  res[regex];
                        }
                        if (l < conf2-2) {
                          req += ", ";
                        }else {
                          req += "NOW()";
                        }
                        regex += 2;
                      }
                    }
                    std::cout << req << '\n';
                    requete->update(req);
                  }
                }else{
                  ResSql = requete->select("home","now() - date_temp","");
                  std::string::size_type size;
                  int num = std::stoi(ResSql[0][0], &size);
                  std::cout << num << '\n';
                  if (num > 30) {
                  req = "UPDATE home SET ";
                  for (int l = 0; l < conf2; l++) {
                    if (config[3][l] != "null") {
                      req += config[3][l];
                      req += " = ";
                      if (res[regex] != "") {
                        req +=  res[regex];
                      }
                      if (l < conf2-2) {
                        req += ", ";
                      }else {
                        req += "NOW()";
                      }
                      regex += 2;
                    }
                  }
                }
                  std::cout << req << '\n';
                  requete->update(req);
                }
              }else{
                ResSql = requete->select("home","now() - date_temp","");
                std::string::size_type size;
                int num = std::stoi(ResSql[0][0], &size);
                std::cout << num << '\n';
                if (num > 30) {
                req = "UPDATE home SET ";
                for (int l = 0; l < conf2; l++) {
                  if (config[3][l] != "null") {
                    req += config[3][l];
                    req += " = ";
                    if (res[regex] != "") {
                      req +=  res[regex];
                    }
                    if (l < conf2-2) {
                      req += ", ";
                    }else {
                      req += "NOW()";
                    }
                    regex += 2;
                    }
                  }
                }
                std::cout << req << '\n';
                requete->update(req);
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
