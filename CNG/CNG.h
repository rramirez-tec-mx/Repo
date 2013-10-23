#pragma once
#include "CNGApi.h"

class CNG_EXPORTS_API CNG
{
public:
	CNG(void);
	~CNG(void);
public:
	int EchhoNumber(int number);
	int CheckIfFipsIsEnabled();	
};




