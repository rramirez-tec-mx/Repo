#pragma once
#include <windows.h>
#include <string>
#include "CNGApi.h"


class DLL_EXPORT CryptRandomNumberGenerator
{
public:
	CryptRandomNumberGenerator(void);
	~CryptRandomNumberGenerator(void);

public:
	std::wstring Generate(std::wstring algType, int lengthRandomByteArray);
};

