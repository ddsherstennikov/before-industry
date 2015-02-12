#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <math.h>
#include "matrix.h"
using namespace std;

double K(double x, double y)
{
	return x*y;
}

bool itsokay(double N, int *dims)
{
	if ( fmod(N, dims[0]) )
		return false;
	if ( fmod(N, dims[1]) )
		return false;
	return true;
}

void mout(matrix &m, char * name)
{
	cout << endl;
	for (int i = 0 ; i < m.rows() ; i++)
	{
		cout << endl;
		if ( i == m.rows()/2 ) cout << name << " = ";
		else for (int k = 0; k < strlen(name) + 3; k++) cout << ' ';
		for (int j = 0; j < m.columns() ; j++)
			if (!j)
				cout << ' ' << m(i,j);
			else
				cout << setw(10) << m(i,j);
	}
}

double fillin(int i,int j, double a, double h)
{
	return i == j ? ( h * K( a + h/2 + i*h, a + h/2 + j*h ) ) : ( h * K( a + h/2 + i*h, a + h/2 + j*h ) ) ;
}

double fillinf(int i, double a, double h)
{
	return  2 * (a + h/2 + i * h) / 3;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int iter = 16;
	int N = 10;
	double a = 0;
	double b = 1;
	double h = (b - a) / N;
	int dims[2] = {0, 0};

	MPI_Dims_create(size, 2, dims);

	if ( !rank )
		cout << size << " processes make " << dims[0] << 'x' << dims[1] << " grid :)" << endl;

	if ( !itsokay(N, dims) )
	{
		if (!rank)
			cout << endl << "Нах иди !" << endl << 
			"Меняй либо кол-во процессов либо количество уравнений!" << endl;
		MPI_Finalize();
		return 0;
	}
	
	int width  = dims[0];
	int height = dims[1];

	matrix Afull(N, N);
	matrix A(N/height, N/width);
	matrix ffull(N , 1);
	matrix f(N/width, 1);
	matrix ui(N/width, 1);
	matrix ufull(N, 1);
	matrix au(N/width, 1);
	matrix aufull(N, 1);
	matrix aui(N, 1);

	for (int i = 0; i < A.rows(); i++)
	{
		for (int j = 0; j < A.columns(); j++)
		{
			A(i,j) = fillin( ( rank / width ) * (N/height) + i, (rank % width) * (N/width) + j, a, h );
		}
	}

	for (int i = 0; i < Afull.rows(); i++)
		for (int j = 0; j < Afull.columns(); j++)
		{
			Afull(i,j) = fillin(i,j,a,h);
		}
	
	for (int i = 0; i < f.rows(); i++)
		for (int j = 0; j < f.columns(); j++)
		{
			f(i, 0) = fillinf( ( rank % width ) * (N/width) + i , a, h);
		}
	
	for (int i = 0; i < ffull.rows(); i++)
		for (int j = 0; j < ffull.columns(); j++)
		{
			ffull(i,j) = fillinf(i,a,h);
		}

	MPI_Comm MY_COMM_HOR, MY_COMM_VER;

	MPI_Comm_split(MPI_COMM_WORLD, rank / width , rank, &MY_COMM_HOR);
	
	MPI_Comm_split(MPI_COMM_WORLD, rank % width , rank, &MY_COMM_VER);

	au = f;

	iter = 16;
	for (int k = 0; k < iter ; k++)
	{
		au = A * au;
		MPI_Allreduce(MPI_IN_PLACE, &au(0,0), au.rows(), MPI_DOUBLE, MPI_SUM, MY_COMM_HOR);
		MPI_Allgather(&au(0,0), au.rows(), MPI_DOUBLE, &aui(0,0), au.rows(), MPI_DOUBLE, MY_COMM_VER);
		aufull = aui + ffull;
		au = f;
		MPI_Scatter(&aufull(0,0), au.rows() , MPI_DOUBLE, &au(0,0), au.rows(), MPI_DOUBLE, 0, MY_COMM_HOR);
	}
	if (!rank)
			mout(aufull, "u");

	MPI_Finalize();
	return 0;
}