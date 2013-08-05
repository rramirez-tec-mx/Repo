#pragma once
#include <windows.h>
#include <string>

#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT CryptRandomNumberGenerator
{
public:
	CryptRandomNumberGenerator(void);
	~CryptRandomNumberGenerator(void);

public:
	std::wstring Generate(std::wstring algType, int lengthRandomByteArray);
};

