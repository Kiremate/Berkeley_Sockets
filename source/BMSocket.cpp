#include "../headers/BMSocket.h"
// by default it creates a IPv4 TCP socket
BMSocket::BMSocket()
{
	this->mainSocket = socket(AF_INET, SOCK_STREAM, 0);
}

BMSocket::~BMSocket()
{
	shutdown(this->mainSocket, SD_SEND);
}
