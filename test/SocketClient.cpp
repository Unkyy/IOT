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
  if(connect(socket_client, (struct sockaddr *) &sin, sizeof sin) == SOCKET_ERROR){
    perror("connect()");

    exit(errno);
  }
}

void SocketClient::send_server(std::string id, std::string etat){
  std::string buffer;
  buffer = "<commande><id>"+ id +"</id><bool>"+ etat +"</bool></commande>";

  if(send(socket_client, buffer.c_str(), buffer.length(), 0) == SOCKET_ERROR)
  {
    perror("send()");
    exit(errno);
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
