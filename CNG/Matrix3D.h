#pragma once
#include "CNGApi.h"
#include <vector>

class DLL_EXPORT CMatrix3D
{
public:
	CMatrix3D(void);
	~CMatrix3D(void);
	static double Interp3(std::vector<std::vector<double>> & matrix3D, std::vector<double> depthVector, double interpPointX, double interpPointY, double interpPointZ, std::vector<double> & xBreakPoints, std::vector<double> & yBreakPoints, bool isRowMajorOrder);
	static double Interp3Inverse(std::vector<std::vector<double>> & matrix3D, std::vector<double> depthVector, double interpPointX, double interpPointY, double interpPointZ, std::vector<double> & xBreakPoints, std::vector<double> & yBreakPoints, bool isRowMajorOrder);	
	static double Interp3Inverse(std::vector<std::vector<double>> & matrix3D, std::vector<double> depthVector, double interpPointX, double interpPointY, double interpPointZ, std::vector<double> & xBreakPoints, std::vector<double> & yBreakPoints, const char dimensionToInverte, bool isRowMajorOrder);
};

