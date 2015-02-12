#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <windows.h>
using namespace std;

//�������� �������
DWORD WINAPI ThreadFunction(PVOID pParam);

//����� �����������
const short PROCESSORS_NUMBER = 4;

//� ���� ���-�� ����� ���������� ��������� �������
struct info
{
	double side;
	int fragNumber;
	int processorsNumber;
	int currentProcess;
	double sum;
};


double f(const double x, const double z);
double calculateSimpleVolume(double a, double height);
double calculateIntegral(double a, int fragNumber, double (*function)(const double x, const double z));
double partialcalculateIntegral(double a,int fragNumber, int iStart, int iStop, double (*function)(const double x, const double z));

double calculateIntegral(double a, int fragNumber, double (*function)(const double x, const double z))
{
	double sum = 0;

	//������ ~���������
	HANDLE *hThreads = new HANDLE[PROCESSORS_NUMBER - 1];

	// ������� ������ ����������
	info *threadInfo = new info[PROCESSORS_NUMBER];

	// ������ ������, ��������� ������ ���-���
	for(int i = 0; i < PROCESSORS_NUMBER; i++)
	{
		threadInfo[i].fragNumber = fragNumber;
		threadInfo[i].side = a;
		threadInfo[i].currentProcess = i;
		threadInfo[i].processorsNumber = PROCESSORS_NUMBER;
		hThreads[i] = CreateThread(NULL, 0, ThreadFunction, &threadInfo[i], 0, 0);
	}

	ThreadFunction(&threadInfo[0]);

	WaitForMultipleObjects(PROCESSORS_NUMBER - 1, hThreads, TRUE, INFINITE);

	for(int i = 0; i < PROCESSORS_NUMBER; i++)
		sum += threadInfo[i].sum;

	for(int i = 0; i < PROCESSORS_NUMBER - 1; i++)
		CloseHandle(hThreads[i]);

	return sum;
}

//�������� �������� ���� ������� ��� ����������� �������� �� �������
double f(const double x, const double z)
{
	return  sin(x);
}

//�-�� �������� ~������ ������ ���������
double partialcalculateIntegral(double a,int fragNumber, int iStart, int iStop, double (*function)(const double x, const double z))
{
	double sum = 0;
	double z; //�������� ������� � ����� f(x,y)
	for(int i = iStart; i < iStop; i++)
		for(int j = 0; j <= i; ++j)
		{
			z =  function((fragNumber - i + 1/2)*a/fragNumber, (j + 1/2)*a/fragNumber);
			z = z < 0 ? 0 : z;
			z = i==j ? z / 2 : z;
			sum += (a/fragNumber) * (a/fragNumber) * z;
		}
		return sum;
}

DWORD WINAPI ThreadFunction(PVOID pParam)
{
	info *threadInfo = static_cast<info *>(pParam);
	int lConstraint = threadInfo->fragNumber * sqrt(threadInfo->currentProcess/(double)threadInfo->processorsNumber);
	int rConstraint = threadInfo->fragNumber * sqrt((threadInfo->currentProcess + 1.0)/(double)threadInfo->processorsNumber);

	threadInfo->sum = partialcalculateIntegral(
		threadInfo->side, 
		threadInfo->fragNumber,
		lConstraint, 
		rConstraint, 
		f);
	return 0;
}

int main(int argc, char* argv[])
{
	double side = 1.0;
	int fragNumber = 10;
	cout << calculateIntegral(side, fragNumber,f) << endl;
	return 0;
}