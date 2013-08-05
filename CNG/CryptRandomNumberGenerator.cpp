#include "StdAfx.h"
#include "CryptRandomNumberGenerator.h"
#include "StringHelper.h"
#include <string>

using namespace std;

CryptRandomNumberGenerator::CryptRandomNumberGenerator(void)
{
}


CryptRandomNumberGenerator::~CryptRandomNumberGenerator(void)
{
}

wstring CryptRandomNumberGenerator::Generate(wstring algType, int lengthRandomByteArray)
{
	BCRYPT_ALG_HANDLE hAlgorithm = NULL;
	StringHelper stringHelper;
	
	ULONG cbBuffer = lengthRandomByteArray;;
	PUCHAR pbBuffer = NULL;
	ULONG dwFlags = BCRYPT_RNG_USE_ENTROPY_IN_BUFFER;;
	NTSTATUS res;
	wstring resultRandomString;
	
	res = BCryptOpenAlgorithmProvider(&hAlgorithm, algType.c_str(), NULL, 0);

	pbBuffer = new UCHAR[cbBuffer];
	res = BCryptGenRandom(hAlgorithm, pbBuffer, cbBuffer, dwFlags);
	res = BCryptCloseAlgorithmProvider(hAlgorithm, 0);

	resultRandomString = stringHelper.ConvertByteArrayToString(pbBuffer, cbBuffer);

	if(NULL != pbBuffer)
	{
		delete[] pbBuffer;
		pbBuffer = NULL;
	}

	return resultRandomString;
}