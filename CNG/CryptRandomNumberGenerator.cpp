#include "StdAfx.h"
#include "CryptRandomNumberGenerator.h"
#include "StringHelper.h"
#include <string>
#include <vector>
using namespace std;

CryptRandomNumberGenerator::CryptRandomNumberGenerator(void)
{
}


CryptRandomNumberGenerator::~CryptRandomNumberGenerator(void)
{
}

wstring CryptRandomNumberGenerator::Generate(const wstring & algType, int lengthRandomByteArray)
{
	BCRYPT_ALG_HANDLE hAlgorithm = NULL;
	StringHelper stringHelper;
	
	ULONG cbBuffer = lengthRandomByteArray;;
	vector<UCHAR> pbBuffer;
	ULONG dwFlags = BCRYPT_RNG_USE_ENTROPY_IN_BUFFER;;
	NTSTATUS res;
	wstring resultRandomString;
	
	res = BCryptOpenAlgorithmProvider(&hAlgorithm, algType.c_str(), NULL, 0);

	pbBuffer.resize(cbBuffer);
	res = BCryptGenRandom(hAlgorithm, &pbBuffer[0], cbBuffer, dwFlags);
	res = BCryptCloseAlgorithmProvider(hAlgorithm, 0);

	resultRandomString = stringHelper.ConvertByteArrayToString(&pbBuffer[0], cbBuffer);

	return resultRandomString;
}