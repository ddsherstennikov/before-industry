//This is an implementation of the "matrix" class

#include "matrix.h"

matrix::matrix(int rows, int columns)
{
	n = rows;
	m = columns;
	a = new double[n*m];
	for (int i = 0; i < n*m; i++)
		a[i] = 0;
}

matrix::~matrix()
{
	delete []a;
}

matrix::matrix(const matrix& x)
{
	n = x.n;
	m = x.m;
	a = new double[n*m];
	for (int i = 0; i < n*m; i++)
		a[i] = x.a[i];
}

matrix & matrix::operator = (const matrix& x)
{
	if (&x != this)
	{
		delete []a;
		n = x.n;
		m = x.m;
		a = new double[n*m];
		for (int i = 0; i < n*m; i++)
			a[i] = x.a[i];
	}
	return *this;
}

matrix & matrix::operator += (const matrix& x)
{
	if ( n != x.n || m != x.m)
		throw dimentionsMismatch();
	for (int i = 0; i < n*m; i++)
		a[i] += x.a[i];
	return *this;
}

matrix & matrix::operator -= (const matrix& x)
{
	if ( n != x.n || m != x.m)
		throw dimentionsMismatch();
	for (int i = 0; i < n*m; i++)
		a[i] -= x.a[i];
	return *this;
}

/*
matrix & matrix::operator *= (const matrix& x)
{

}
*/

matrix operator + (const matrix& x, const matrix& y)
{
	matrix z(x);
	z += y;
	return z;
}

matrix operator - (const matrix& x, const matrix& y)
{
	matrix z(x);
	z -= y;
	return z;
}

matrix operator * (const matrix& x, const matrix& y)
{
	if (x.m != y.n)
		throw matrix::dimentionsMismatch();
	matrix z(x.n, y.m);
	for (int i = 0 ; i < z.n ; i++)
		for (int j = 0; j < z.m ; j++)
			for (int k = 0; k < x.m ; k++)
				z(i,j) += x(i,k) * y(k,j);
	return z;
}

double & matrix::operator () (int row, int column) const
{
	return a[ row * m + column];
}

int matrix::rows()
{
	return n;
}

int matrix::columns()
{
	return m;
}