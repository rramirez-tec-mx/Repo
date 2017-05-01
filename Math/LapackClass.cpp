#include "LapackClass.h"
#include <stdio.h>
#include <vector>
#include "Matrix.h"
#include <algorithm>
#include "mkl.h"
using namespace std;

LapackClass::LapackClass(void)
{
}


LapackClass::~LapackClass(void)
{
}

void LapackClass::calcMatrix()
{
    double A[9] = {3, 4, 5, 1, 2, 4, 5, 1, 3};
    double b[3] = {1,2,3};

    int N = 3;
    int nrhs = 1;
    int lda = 3;
    int ipiv[3];
    int ldb = 3;
    int info;
    
	dgesv(&N, &nrhs, A, &lda, ipiv, b, &ldb, &info);

    if(info == 0) /* succeed */
	printf("The solution is %lf %lf %lf\n", b[0], b[1], b[2]);
    else
	fprintf(stderr, "dgesv_ fails %d\n", info);
	
	
}

void LapackClass::calcMatrix2(double *matrixC)
{

	//perform C = alpha*A*B + beta*C. 
	// if beta equal 0, no C must be provided
	//so this is the product C = A*B
			
	double alpha = 1.0;
	double beta = 0.0;
	int lda = 3;    

	int rowsOfMatrixA = 3;
	
	vector<double> matrixA;
	//first column of A
	matrixA.push_back(1);
	matrixA.push_back(5);
	matrixA.push_back(2);
	//second column of A
	matrixA.push_back(1);
	matrixA.push_back(2);
	matrixA.push_back(4);
	//third column of A
	matrixA.push_back(5);
	matrixA.push_back(3);
	matrixA.push_back(7);
     
	int columnsOfMatrixA = (int)matrixA.size();
	int columnsOfMatrixB = 1;	
	vector<double> matrixB;
	matrixB.push_back(1);
	matrixB.push_back(1);
	matrixB.push_back(1);
							   		
	int ldc = 3;    
	
	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, rowsOfMatrixA,
		columnsOfMatrixB, columnsOfMatrixA, alpha, matrixA.data(), lda, matrixB.data(),
		rowsOfMatrixA, beta, matrixC, ldc);
}


void LapackClass::calcMatrixProduct(CMatrix& A, vector<double> & B, vector<double> & C, int columnsOfMatrixB, CBLAS_TRANSPOSE transposeA, CBLAS_TRANSPOSE transposeB)
{

	//perform C = alpha*A*B + beta*C. 
	// if beta equal 0, no C must be provided
	//so this is the product C = A*B
			
	double alpha = 1.0;
	double beta = 0.0;

	auto rowsOfMatrixA  = (int)A.m_Data.at(0).size();
	auto columnsOfMatrixA  = (int)A.m_Data.size();
	auto lda = (int)max(A.m_Data.at(0).size(),A.m_Data.size());
							   		
	auto ldc = rowsOfMatrixA;

	C.assign(rowsOfMatrixA*columnsOfMatrixB,0);
	
	double *matrixAInternal = new double[rowsOfMatrixA*columnsOfMatrixA];
	for (int i=0; i< rowsOfMatrixA; i++)
		for (int j=0; j< columnsOfMatrixA; j++)
		{
			matrixAInternal[i*rowsOfMatrixA+j] = A.m_Data[i][j];
		}

	 cblas_dgemm(CblasColMajor, transposeA, transposeB, rowsOfMatrixA,
		 columnsOfMatrixB, columnsOfMatrixA, alpha, matrixAInternal, lda, B.data(),
		 rowsOfMatrixA, beta, C.data(), ldc);


	 delete[] matrixAInternal;
}

void LapackClass::InvertMatrix(vector<double> & flattenMatrix)
{
	
	int error = 10;
	
	int rows = (int)sqrt((double)flattenMatrix.size());
	int * ipiv = new int[rows*rows];
	
	dgetrf_(&rows, &rows, &flattenMatrix[0], &rows, ipiv, &error);

	error = 10;
	
	int lwork = rows;
	double *work = new double[lwork];

	dgetri_(&rows, &flattenMatrix[0], &rows, ipiv, work, &lwork, &error );
	
	
	delete[] ipiv;
	delete[] work;
}

