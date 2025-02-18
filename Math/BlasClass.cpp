#include "BlasClass.h"
#include <vector>
#include <ppl.h>
#include "mkl.h"
using namespace std;
using namespace concurrency;

void DAXPIDENOALTRI(int *n, double *sa, double *sx, int *incx, double *sy, int *incy)
{
	incx;
	incy;
	for (int i = 0; i < *n; i++)
	{
		sy[i] = sx[i] * sa[0] + sy[i];
	}
}

BlasClass::BlasClass()
{
}


BlasClass::~BlasClass()
{
}

void BlasClass::ScaleVector()
{
	double A[3] = {1,2,3};
	int N = 3;
	double alpha = 2;
	int incx = 1;

	cblas_dscal(N, alpha, A, incx);
}

void BlasClass::ScaleAndSumVector()
{
	//alpha*A + B --> B

	double A[3] = { 1, 2, 3 };
	double B[3] = { -1, -1, -1 };
	int N = 3;
	double scale = 2;
	int incx = 1;
	int incy = 1;

	cblas_daxpy(N, scale, A, incx, B, incy);
}

void BlasClass::ScaleAndSumVectorAndSquare()
{
	//alpha*A + B --> B

	double A[3] = { -1, -1, -1 };
	double B[3] = { 10, 20, 3 };
	int N = 3;
	double scale = 7;
	
	int incx = 1;
	int incy = 1;

	cblas_daxpy(N, scale, A, incx, B, incy);

	for (int i = 0; i < N; i++)
	{
		B[i] *= B[i];
	}


	auto indexMax = cblas_idamax(N, B, incx); //occhio che l'uscita � uno based
	indexMax;

	//auto indexMin = idamin_(&N, B, &incx); //occhio che l'uscita � uno based
	//indexMin;
}

size_t BlasClass::ComputeDistanceAndReturnMax(double *X, double *Y, double *Z, int N, double xc, double yc, double zc, vector<double> & minusOne, vector<double> & out)
{
	int incx = 1;
	int incy = 1;

	//calcolo del vettore [(x1-xc) (x2-xc) ... (xn-xc)] --> X
	cblas_daxpy(N, xc, &minusOne[0], incx, X, incy);

	//calcolo del vettore [(y1-xc) (y2-xc) ... (yn-xc)] --> Y
	cblas_daxpy(N, yc, &minusOne[0], incx, Y, incy);

	//calcolo del vettore [(z1-xc) (z2-xc) ... (zn-xc)] --> Z
	cblas_daxpy(N, zc, &minusOne[0], incx, Z, incy);

	//elevamento al quadrato dei 3 vettori 
	//parallel_for(size_t(0), (size_t)N, [&](size_t i)
	for (int i = 0; i < N; i++)
	{
		X[i] *= X[i];
		Y[i] *= Y[i];
		Z[i] *= Z[i];
	}
	//});

	//calcolo il vettore di uscita come somma delle componenti dei 3 vettori parziali
	double uno = 1;
	cblas_daxpy(N, uno, X, incx, &out[0], incy);
	cblas_daxpy(N, uno, Y, incx, &out[0], incy);
	cblas_daxpy(N, uno, Z, incx, &out[0], incy);

	auto indexMax = cblas_idamax(N, &out[0], incx); //occhio che l'uscita � uno based
	
	return indexMax - 1;
}

size_t BlasClass::ComputeDistanceAndReturnMin(double *X, double *Y, double *Z, int N, double xc, double yc, double zc, vector<double> & minusOne, vector<double> & out)
{
	int incx = 1;
	int incy = 1;

	//calcolo del vettore [(x1-xc) (x2-xc) ... (xn-xc)] --> X
	cblas_daxpy(N, xc, &minusOne[0], incx, X, incy);

	//calcolo del vettore [(y1-xc) (y2-xc) ... (yn-xc)] --> Y
	cblas_daxpy(N, yc, &minusOne[0], incx, Y, incy);

	//calcolo del vettore [(z1-xc) (z2-xc) ... (zn-xc)] --> Z
	cblas_daxpy(N, zc, &minusOne[0], incx, Z, incy);

	//elevamento al quadrato dei 3 vettori 
	//parallel_for(size_t(0), (size_t)N, [&](size_t i)
	for (int i = 0; i < N; i++)
	{
		X[i] *= X[i];
		Y[i] *= Y[i];
		Z[i] *= Z[i];
	}
	//});

	//calcolo il vettore di uscita come somma delle componenti dei 3 vettori parziali
	double uno = 1;
	cblas_daxpy(N, uno, X, incx, &out[0], incy);
	cblas_daxpy(N, uno, Y, incx, &out[0], incy);
	cblas_daxpy(N, uno, Z, incx, &out[0], incy);

	auto smallest = std::min_element(std::begin(out), std::end(out));
	return std::distance(std::begin(out), smallest);
}


size_t BlasClass::ComputeDistanceAndReturnMinMale(double *X, double *Y, double *Z, int N, double xc, double yc, double zc, vector<double> & minusOne, vector<double> & out)
{
	minusOne;
	for (int i = 0; i < N; i++)
	{
		out[i] = std::pow((xc - X[i]), 2) + std::pow((yc - Y[i]), 2) + std::pow((zc - Z[i]), 2);
	}

	auto smallest = std::min_element(std::begin(out), std::end(out));
	return std::distance(std::begin(out), smallest);
}