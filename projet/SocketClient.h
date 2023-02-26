#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <pthread.h>         // std::thread
#include <regex>

#include "ReqSql.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close

#define nb_user 10
#define taille_max 1024

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;




class SocketClient{
  public:
      SocketClient(int port);
      void send_server(std::string id, std::string etat);
      void Sock_connect();
      void regul();
      ~SocketClient();
      void sendValue_server(std::string temp);
    protected:
      SOCKET socket_client;
      sockaddr_in sin = { 0 };
      char msg[taille_max];
      int nb_octet;
      ReqSql * requete = new ReqSql();
      std::vector<std::vector<std::string>> ResSql;
};
#endif
