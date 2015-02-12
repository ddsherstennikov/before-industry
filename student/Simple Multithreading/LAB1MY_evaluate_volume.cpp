// LAB1_evaluate_volume.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <windows.h>

#define R 5.0
#define N 1000
#define A 3.0
#define h (A/N)
#define NUM_THREADS 4
using namespace std;

inline double sqr(double x)
{
	return ( x*x );
}

double f(double x, double y)
{
	return ( sqrt( sqr(R) - sqr(x) - sqr(y) ) );
}

struct thr_param
{
	int begin;
	int end;
	double result;
};

DWORD WINAPI thr_proc(LPVOID param)
{
	thr_param &p = *static_cast<thr_param *>(param);
	double c = 0.0;

	for(int i=p.begin;i<=p.end;i++)
		for(int j=0;j<=i;j++)
		{
			c = (j<i) ? sqr(h) : (sqr(h)/2);
			p.result += f( (N-i-0.5)*h, (j+0.5)*h ) * c;
		}
	return p.result;
}


int _tmain(int argc, _TCHAR* argv[])
{
	double V = 0.0;
	double c = 0.0;

	thr_param param[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++)
	{
		param[i].begin = N * sqrt(k/N);
		param[i].end = N * sqrt((k+N/N);
		param[i].result = 0.0;
	}

	//::CreateThread(NULL, 0, thr_proc, &param[i], 0, &dwId[i]);
	
	return 0;
}

	/*STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset( &si, 0, sizeof(STARTUPINFO) );
	memset( &pi, 0, sizeof(PROCESS_INFORMATION) );
	BOOL isCreated = CreateProcess( argv[1], NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (!isCreated)
		printf( "0x%08X", GetLastError() );*/