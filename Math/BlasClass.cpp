#include "BlasClass.h"
#include <vector>

using namespace std;

extern "C" int dscal_(int *n, double *sa, double *sx, int *incx);
extern "C" int daxpy_(int *n, double *sa, double *sx, int *incx, double *sy, int *incy);
extern "C" int idamax_(int *n, double *sx, int *incx);



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

	dscal_(&N, &alpha, A, &incx);
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

	daxpy_(&N, &scale, A, &incx, B, &incy);
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

	daxpy_(&N, &scale, A, &incx, B, &incy);

	for (int i = 0; i < N; i++)
	{
		B[i] *= B[i];
	}


	auto indexMax = idamax_(&N, B, &incx); //occhio che l'uscita è uno based
	indexMax;

	//auto indexMin = idamin_(&N, B, &incx); //occhio che l'uscita è uno based
	//indexMin;
}

size_t BlasClass::ComputeDistanceAndReturnMax(double *X, double *Y, double *Z, int N, double xc, double yc, double zc, vector<double> & minusOne, vector<double> & out)
{


	int incx = 1;
	int incy = 1;

	//calcolo del vettore [(x1-xc) (x2-xc) ... (xn-xc)] --> X
	daxpy_(&N, &xc, &minusOne[0], &incx, X, &incy);

	//calcolo del vettore [(y1-xc) (y2-xc) ... (yn-xc)] --> Y
	daxpy_(&N, &yc, &minusOne[0], &incx, Y, &incy);

	//calcolo del vettore [(z1-xc) (z2-xc) ... (zn-xc)] --> Z
	daxpy_(&N, &zc, &minusOne[0], &incx, Z, &incy);

	//elevamento al quadrato dei 3 vettori 
	for (int i = 0; i < N; i++)
	{
		X[i] *= X[i];
		Y[i] *= Y[i];
		Z[i] *= Z[i];
	}

	//calcolo il vettore di uscita come somma delle componenti dei 3 vettori parziali
	double uno = 1;
	daxpy_(&N, &uno, X, &incx, &out[0], &incy);
	daxpy_(&N, &uno, Y, &incx, &out[0], &incy);
	daxpy_(&N, &uno, Z, &incx, &out[0], &incy);



	auto indexMax = idamax_(&N, &out[0], &incx); //occhio che l'uscita è uno based
	
	return indexMax - 1;
}