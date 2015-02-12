// class matrix is defined in this file.

class matrix
{
private:
	int n;
	int m;
	double* a;
	//exceptions:
	static class dimentionsMismatch
	{
		public: dimentionsMismatch(){}
	};

public:
	matrix(int rows, int columns);
	matrix(const matrix& m);
	~matrix();

	matrix & operator =  (const matrix& m);
	matrix & operator += (const matrix& m);
	matrix & operator -= (const matrix& m);
	//matrix & operator *= (const matrix& m);

	friend matrix operator + (const matrix& x, const matrix& y);
	friend matrix operator - (const matrix& x, const matrix& y);
	friend matrix operator * (const matrix& x, const matrix& y);
	double & operator () (int row, int column) const;

	int rows();
	int columns();
};