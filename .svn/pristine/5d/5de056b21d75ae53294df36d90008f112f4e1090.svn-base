#pragma once
#include <Windows.h>

#define DLL_EXPORT __declspec(dllexport)


class DLL_EXPORT CNG
{
public:
	CNG(void);
	~CNG(void);
public:
	int EchhoNumber(int number);
	int CheckIfFipsIsEnabled();
	void EnumCrypyProvider(LPCWSTR pszAlgId, BCRYPT_PROVIDER_NAME **ppImplList, ULONG & pImplCount);
};




