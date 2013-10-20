#pragma once
#include "CNGApi.h"
#include <vector>

class DLL_EXPORT CMatrix3D
{
public:
	CMatrix3D(void);
	~CMatrix3D(void);
	static double Interp3(const std::vector<std::vector<double>> & matrix3D, const std::vector<double> & depthVector, double interpPointX, double interpPointY, double interpPointZ, const std::vector<double> & xBreakPoints, const std::vector<double> & yBreakPoints, bool isRowMajorOrder);
	static double Interp3Inverse(const std::vector<std::vector<double>> & matrix3D, const std::vector<double> & depthVector, double interpPointX, double interpPointY, double interpPointZ, const std::vector<double> & xBreakPoints, const std::vector<double> & yBreakPoints, bool isRowMajorOrder);	
	static double Interp3Inverse(const std::vector<std::vector<double>> & matrix3D, const std::vector<double> & depthVector, double interpPointX, double interpPointY, double interpPointZ, const std::vector<double> & xBreakPoints, const std::vector<double> & yBreakPoints, const char dimensionToInverte, bool isRowMajorOrder);
};

