#pragma once
#include "MathApi.h"
#include <vector>
class MATH_EXPORTS_API BlasClass
{
public:
	BlasClass();
	~BlasClass();
	void ScaleVector();
	void ScaleAndSumVector();
	void ScaleAndSumVectorAndSquare();
	size_t ComputeDistanceAndReturnMax(double *X, double *Y, double *Z, int N, double xc, double yc, double zc, std::vector<double> & minusOne, std::vector<double> & out);
	size_t ComputeDistanceAndReturnMin(double *X, double *Y, double *Z, int N, double xc, double yc, double zc, std::vector<double> & minusOne, std::vector<double> & out);
	size_t ComputeDistanceAndReturnMinMale (double *X, double *Y, double *Z, int N, double xc, double yc, double zc, std::vector<double> & minusOne, std::vector<double> & out);
};

