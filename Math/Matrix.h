#pragma once
#include "MathApi.h"
#include <vector>
#pragma warning (disable : 4251)

class MATH_EXPORTS_API CMatrix
{
public:
	CMatrix(int sizeX, int sizeY);
	~CMatrix(void);
public:
	std::vector<std::vector<double>> m_Data;
	
};

