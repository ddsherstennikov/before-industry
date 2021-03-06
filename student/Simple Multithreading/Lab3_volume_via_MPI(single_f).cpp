// Lab3.1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "windows.h"
#include <mpi.h>
#include <cmath>
#include <iostream>
using namespace std;

#define MAIN_PROCESS 0
#define WRONG_VALUE 0
#define ERROR 404

double f(const double x, const double y);
double partialIntegral(double a,int piecesNumber, int iStart, int iStop, double (*f)(const double x, const double y));

int main(int argc, char* argv[])
{
	int	_state	= EXIT_FAILURE;

	double localRes		= 0.0;
	double globalRes	= 0.0;
	double side;
	int piecesNumber;

	int 	processId;
	int 	processesQuantity;

	MPI_Request	req;
	MPI_Status	stat;

	//�������������
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&processesQuantity);
	MPI_Comm_rank(MPI_COMM_WORLD,&processId);

	try
	{
		//��� ��������� �������� ��������� ���-�� ��������� ������ � ��������� � ������ �� ��������������� ���������
		if (processId == MAIN_PROCESS)
		{ 
			side = atof(argv[1]);
			piecesNumber = atoi(argv[2]);

			if(side < 0 || piecesNumber < 0) throw  WRONG_VALUE;

			for (int i = 1; i < processesQuantity; i++)
			{
				MPI_Isend(&side, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &req);
				MPI_Isend(&piecesNumber, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &req);
			}
		}
		//��� ���������������� �������� �������� ���-�� �� ���������
		else 
		{
			MPI_Recv(&side, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
			MPI_Recv(&piecesNumber, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
		}

		//��� ���� ��������� - ������������ ������� � ��������� �����
		int lConstraint = (int)(piecesNumber * sqrt(processId/(double)processesQuantity));
		int rConstraint = (int)(piecesNumber * sqrt((processId + 1.0f)/(double)processesQuantity));

		localRes = partialIntegral(side, piecesNumber, lConstraint, rConstraint, f);

		//��� ��������� �������� - ��������� ��������� ���-�� �����. ����. � �������� ������ ���������
		if (processId == MAIN_PROCESS)
		{ 
			globalRes = localRes;
			for (int i = 1; i < processesQuantity; i++)
			{
				MPI_Recv(&localRes, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
				globalRes += localRes;
			}
			cout << "Result: " << globalRes << endl;
		}
		//��� �����. ��������� - �������� ��������� ���-�
		else 
		{
			MPI_Send(&localRes, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}

		_state = EXIT_SUCCESS;

	} 
	catch(...)
	{
		MPI_Abort(MPI_COMM_WORLD, ERROR);
		cout << "Error on process number: " << processId << endl;
	}

	MPI_Request_free(&req);
	MPI_Finalize();

	return _state;
}

//������������� �-��
double f(const double x, const double y)
{
	return sin(x);
}

//��������� ��������
double partialIntegral(double a,int piecesNumber, int iStart, int iStop, double (*f)(const double x, const double y))
{
	 	double result = 0;
	 	double z;
		for(int i = iStart; i < iStop; i++)
			for(int j = 0; j <= i; ++j)
	 		{
	 			z =  f((piecesNumber - i + 1/2)*a/piecesNumber, (j + 1/2)*a/piecesNumber);
	 			z = z < 0 ? 0 : z;
	 			z = i==j ? z / 2 : z;
	 			result += (a/piecesNumber) * (a/piecesNumber) * z;
	 		}
	 		return result;
}