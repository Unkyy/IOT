#include "SocketClient.h"

SocketClient::SocketClient(int port){
  socket_client = socket(AF_INET , SOCK_STREAM , 0);
  if(socket_client == INVALID_SOCKET)
  {
      perror(" C socket()");
      exit(errno);
  }
  puts("C Socket created");
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
}

void SocketClient::Sock_connect(){
  while(connect(socket_client, (struct sockaddr *) &sin, sizeof sin) == SOCKET_ERROR){
    sleep(1);
    // perror("connect");
    // exit(errno);
  }
}

void SocketClient::send_server(std::string id, std::string etat){
  std::string buffer;
  ResSql = requete->select("actionneur","etat","id_actionneur = " + id);
  if (ResSql[0][0] != etat) {
    requete->update("update actionneur set etat = "+ etat + " where id_actionneur = " + id );
    if (etat == "1") {
      buffer = "<commande><id>"+ id +"</id><bool>true</bool></commande>";
    }else{
      buffer = "<commande><id>"+ id +"</id><bool>false</bool></commande>";
    }
    if(send(socket_client, buffer.c_str(), buffer.length(), 0) == SOCKET_ERROR)
    {
      perror("send()");
      exit(errno);
    }
  }
}

void SocketClient::sendValue_server(std::string temp){
  std::string buffer;
  buffer = "<temp><id_capteur>78</id_capteur><float>"+ temp +"</float><float>20.0</float></temp>";

  if(send(socket_client, buffer.c_str(), buffer.length(), 0) == SOCKET_ERROR)
  {
    perror("send()");
    exit(errno);
  }
}

SocketClient::~SocketClient()
{
    closesocket(socket_client);
}
