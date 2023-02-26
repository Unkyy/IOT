#include "SocketServer.h"
#include "Regul.h"
#include <iostream>
#include <vector>
#include <thread>
#include <string>

void thread_server(SocketServer *server,SocketClient *commande,int sock){
  
  server->client(sock, commande);
  while (1) {

    server->Tram_client(sock, commande);
  }
}
void regul_chauf(Regul *client){
  //client->commande_chauffage();

 }
 void regul_lum(Regul *client){

   //client->commande_allum();

  }

int main(int argc, char *argv[])
{
    int  sock;
    int i = 3;
    std::vector<std::thread> myThreads;
    SocketServer *server = new SocketServer(8081);
    Regul *client = new Regul(8082);


    server->listen_server();
    while (1) {
      sock = server->AcceptClient();
      if(i < sock) {
        if (i == 4) {
          // client->Sock_connect();
          //
          // myThreads.push_back(std::thread(&regul_lum, client));
          // myThreads[myThreads.size() - 1].detach();
          //
          // myThreads.push_back(std::thread(&regul_chauf, client));
          // myThreads[myThreads.size() - 1].detach();
        }
        myThreads.push_back(std::thread(&thread_server,server,client,sock));
        myThreads[myThreads.size() - 1].detach();

        i++;
      }
    }
    return 0;
}
