#include "../headers/BMSocket.h"

// by default it creates a IPv4 TCP socket
template <typename SOCKET_TYPE>
BMSocket<SOCKET_TYPE>::BMSocket()
{
	this->mainSocket = socket(, TYPE, PROTOCOL);
}

template <typename SOCKET_TYPE>
BMSocket<SOCKET_TYPE>::~BMSocket()
{
	shutdown(this->mainSocket, SD_SEND);
}

template<typename SOCKET_TYPE>
void BMSocket<SOCKET_TYPE>::CloseThisSocket()
{
	closesocket(mainSocket);
}
