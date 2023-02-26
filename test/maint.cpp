
#include <iostream>
#include <cstdlib>
#include "SocketClient.h"
#include <stdlib.h>
#include <string>
#include <unistd.h>

int main(){
	//float temp = 18.0;
	SocketClient *client = new SocketClient(8081);
	client->Sock_connect();
float temp;
while (1) {
	for (temp = 18.0; temp < 24.0; temp += 0.1) {
		std:: string value = std::to_string(temp);
		std::cout << "/* message */" << '\n';
		client->sendValue_server(value);
		sleep(1);
	}
	for (; temp > 16.0; temp -= 0.1) {
			std:: string value = std::to_string(temp);
		client->sendValue_server(value);
		sleep(1);
	}
}



	return 0;
}
