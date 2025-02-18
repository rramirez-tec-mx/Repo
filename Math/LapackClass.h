#pragma once
#include "Matrix.h"
#include <vector>
#include "MathApi.h"
#include "mkl_cblas.h"

class MATH_EXPORTS_API LapackClass
{
public:
	LapackClass(void);
	~LapackClass(void);

	void calcMatrix();
	void calcMatrix2(double *matrixC);	
	void calcMatrixProduct(CMatrix & A, std::vector<double> & B, std::vector<double> & C, int columnsOfMatrixB, CBLAS_TRANSPOSE transposeA, CBLAS_TRANSPOSE transposeB);
	void InvertMatrix(std::vector<double> & flattenMatrix);
};

