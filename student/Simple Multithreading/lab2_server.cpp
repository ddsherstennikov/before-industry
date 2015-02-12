#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <winsock2.h>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

const int buf_size = 200;

int main(int argc, char* argv[])
{
	//получаем IP-адрес и номер порта из командной строки
	const char* IP = argv[4];
	int PORT = atoi(argv[5]);
	
	//Инициализация Winsock DLL
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult == NO_ERROR)
	{

		//создаем listener-сокет
		SOCKET listenerSocket;
		listenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (listenerSocket != INVALID_SOCKET)
		{

			//заполняем стр-ру, необходимую для прослушивания 
			sockaddr_in serverInfo;
			serverInfo.sin_family = AF_INET;
			serverInfo.sin_addr.s_addr = inet_addr(IP);
			serverInfo.sin_port = htons(PORT);

			//подключаем listener-сокет к порту
			if (bind(listenerSocket, (SOCKADDR*) &serverInfo, sizeof(serverInfo)) != SOCKET_ERROR)
			{
				int nOfСlients = atoi(argv[1]);
				cout << "Awaiting (" << nOfСlients << ") clients.\n";

				//Слушаем
				if (listen(listenerSocket, nOfСlients) != SOCKET_ERROR)
				{
					//Создаём сокет для принятия соединений и вектор сокетов, чтобы хранить их 
					SOCKET AcceptSocket;
					std::vector<SOCKET> sockets;

					while(nOfСlients--)
					{
						AcceptSocket = accept(listenerSocket, NULL, NULL);
						if(AcceptSocket == SOCKET_ERROR) break;

						sockets.push_back(AcceptSocket);
					}

					closesocket(listenerSocket);

					//передаём данные клиентам (считываем из командной строки)
					float side = atof(argv[2]);
					int piecesNumber = atoi(argv[3]);

					char buf[buf_size] = "";

					//посылаем буфер клиенту
					for(int x = 0; x < sockets.size(); ++x)
					{
						sprintf(buf, "%f %i %i %i", side, piecesNumber, x, sockets.size());
						send(sockets[x], buf, buf_size, 0);
					}

					//формируем результат
					float result = 0;
					for(int x = 0; x < sockets.size(); ++x)
					{			
						recv(sockets[x], buf, buf_size, 0);
						result += atof(buf);
					}
					cout << "Result: " << result;

					for(int i = 0; i < sockets.size(); ++i)
						closesocket(sockets[i]);
				}
			}
		}
	}
	else //выход по ошибке
	{
		cout << "Error.";
		WSACleanup();
		return -1;
	}			

	//стандартный выход
	WSACleanup();
	return 0;
}

