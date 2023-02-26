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
  while (1) {
    sleep(60);
    client->commande_chauffage();
  }
 }
 void regul_lum(Regul *client){
  while (1) {
    sleep(3);
    client->commande_allum();
  }
}
void regul_lum2(Regul *client){
   while (3) {
     sleep(3);
     client->commande_allum2();
   }
 }


int main(int argc, char *argv[])
{
    int  sock;
    int i;
    int l= 0;;
    std::vector<std::thread> myThreads;
    SocketServer *server = new SocketServer(8081);
    Regul *client = new Regul(8082);
    server->listen_server();

    sock = server->AcceptClient();
    i = sock -1;
    while (1) {
      if(i != sock) {

        myThreads.push_back(std::thread(&thread_server,server,client,sock));
        myThreads[myThreads.size() - 1].detach();

        //std::cout << l << '\n';
        if (l ==0) {

          client->Sock_connect();

          myThreads.push_back(std::thread(&regul_lum2, client));
          myThreads[myThreads.size() - 1].detach();

          myThreads.push_back(std::thread(&regul_lum, client));
          myThreads[myThreads.size() - 1].detach();

          myThreads.push_back(std::thread(&regul_chauf, client));
          myThreads[myThreads.size() - 1].detach();
          l++;
        }
      }
      i=sock;
      std::cout <<"la socket"<< sock << '\n';
      std::cout <<"la i"<< i << '\n';
      sock = server->AcceptClient();
      std::cout <<"la socket"<< sock << '\n';
      std::cout <<"la i"<< i << '\n';
    }
    return 0;
}
