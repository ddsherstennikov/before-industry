// Lab4.cpp : Defines the entry point for the console application.
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

	//инициализация
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&processesQuantity);
	MPI_Comm_rank(MPI_COMM_WORLD,&processId);

	try
	{
		//для основного процесса считываем пар-ры командной строки и рассылаем в каждый из вспомогательных процессов
		if (processId == MAIN_PROCESS)
		{ 
			side = atof(argv[1]);
			piecesNumber = atoi(argv[2]);

			if(side < 0 || piecesNumber < 0) throw  WRONG_VALUE;
		}

		//рассылаем все процессам пар-ры
		MPI_Bcast(&side, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Bcast(&piecesNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);

		//для всех процессов - рассчитываем границы и частичную сумму
		int lConstraint = (int)(piecesNumber * sqrt(processId/(double)processesQuantity));
		int rConstraint = (int)(piecesNumber * sqrt((processId + 1.0f)/(double)processesQuantity));

    //рассчитываем частичный интеграл
		localRes = partialIntegral(side, piecesNumber, lConstraint, rConstraint, f);

		//применяем ф-ию агрегирования - суммирование
		MPI_Reduce(&localRes, &globalRes, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (processId == MAIN_PROCESS)	
			cout << "Result: " << globalRes << endl;

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

//интегрируемая ф-ия
double f(const double x, const double y)
{
	return sin(x);
}

//частичный интеграл
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