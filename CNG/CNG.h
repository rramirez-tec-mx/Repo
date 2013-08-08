#pragma once
#include "CNGApi.h"

class DLL_EXPORT CNG
{
public:
	CNG(void);
	~CNG(void);
public:
	int EchhoNumber(int number);
	int CheckIfFipsIsEnabled();	
};




