#pragma once
#include <vector>
#pragma warning (disable : 4251)

#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT CMatrix
{
public:
	CMatrix(int sizeX, int sizeY);
	~CMatrix(void);
public:
	std::vector<std::vector<double>> m_Data;
	
};

