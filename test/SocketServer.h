#ifndef SOCKET_SERVEUR_H
#define SOCKET_SERVEUR_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <thread>         // std::thread
#include <vector>
#include <regex>
#include <sstream>      // std::stringstream

#include "SocketClient.h"
#include "ReqSql.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close

#define  nb_user 10
#define taille_max 1024

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;






class SocketServer
{
    public:
        SocketServer(int port);
        void listen_server();
        void client(int sock,SocketClient *commande);
        void Tram_client(int sock,SocketClient *commande);
        int  AcceptClient();
        ~SocketServer();
    private:
        void Xml_Send_bdd(std::string str,SocketClient *commande,int sock);
        sockaddr_in sin = { 0 };
        char msg[taille_max];
        int nb_octet;
        int mastersocket;
        std::vector<std::vector<std::string>> ResSql;
        std::string cond;
        std::string req;
        ReqSql * requete = new ReqSql();




};
#endif
