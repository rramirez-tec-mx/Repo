#pragma once
#include "CNGApi.h"
#pragma warning (disable : 4251)

class DLL_EXPORT CMatrix
{
public:
	CMatrix(int sizeX, int sizeY);
	~CMatrix(void);
public:
	std::vector<std::vector<double>> m_Data;
	
};

