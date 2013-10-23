#pragma once
#include <string>
#include "CNGApi.h"


class CNG_EXPORTS_API CryptRandomNumberGenerator
{
public:
	CryptRandomNumberGenerator(void);
	~CryptRandomNumberGenerator(void);

public:
	std::wstring Generate(std::wstring algType, int lengthRandomByteArray);
};

