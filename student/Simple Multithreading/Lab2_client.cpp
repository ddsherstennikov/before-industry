// Client.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cmath>
#include <winsock2.h>

const int buf_size = 200;
float f(const float x, const float y);
float partialIntegral(float a,int piecesNumber, int lConstraint, int rConstraint, float (*f)(const float x, const float y));

int main(int argc, char* argv[])
{
	//�������� IP-����� � ����� ����� �� ��������� ������
	const char* IP = argv[1];
	int PORT = atoi(argv[2]);
	
	//������������� Winsock DLL
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) return 1;
	char *ip = "127.0.0.1";

	//������� ������� �����
	SOCKET mySocket;
	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket != INVALID_SOCKET)
	{
		//��������� ���-��, ����������� ��� �����������  
		sockaddr_in clientService;
		clientService.sin_family = AF_INET;
		clientService.sin_addr.s_addr = inet_addr(IP);
		clientService.sin_port = htons(PORT);

		//������������ � ��������� �� ������
		if (connect(mySocket, (SOCKADDR*)&clientService, sizeof(clientService)) != SOCKET_ERROR)
		{
			//����-�������� ������ ����� �����
			char buf[buf_size] = "";

			recv(mySocket, buf, buf_size, 0);

			float side;
			int piecesNumber;
			int processorsNumber;
			int currentN;
			float result;

			//������ ����
			sscanf(buf, "%f %d %d %d", &side, &piecesNumber, &currentN, &processorsNumber);


			int lConstraint = piecesNumber * sqrt(currentN/(float)processorsNumber);
			int rConstraint = piecesNumber * sqrt((currentN + 1.0f)/(float)processorsNumber);

			result = partialIntegral(side, piecesNumber, lConstraint, rConstraint, f);

			//����� � �������� ���-�
			sprintf(buf, "%f", result);
			send(mySocket, buf, strlen(buf), 0);
		}
		else //����� �� ������
		{
			closesocket(mySocket);
			WSACleanup();
			return 1;
		}		
	}

	//����� �����������
	closesocket(mySocket);
	WSACleanup();
	return 0;
}

//����� �-��
float f(const float x, const float y)
{
	return  sin(x);
}

//��������������� ����� �������� ���������
float partialIntegral(float a,int piecesNumber, int lConstraint, int rConstraint, float (*f)(const float x, const float y))
{
	float result = 0;
	float z;
	for(int i = lConstraint; i < rConstraint; i++)
		for(int j = 0; j <= i; ++j)
		{
			z =  f((piecesNumber - i + 1/2)*a/piecesNumber, (j + 1/2)*a/piecesNumber);
			z = z < 0 ? 0 : z;
			z = i==j ? z / 2 : z;
			result += (a/piecesNumber) * (a/piecesNumber) * z;
		}
		return result;
}