#pragma once
#include <string>
#include "CNGApi.h"


class CNG_EXPORTS_API CryptRandomNumberGenerator
{
public:
	CryptRandomNumberGenerator(void);
	~CryptRandomNumberGenerator(void);

public:
	std::wstring Generate(const std::wstring & algType, int lengthRandomByteArray);
};

