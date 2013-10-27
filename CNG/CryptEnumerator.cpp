#include "StdAfx.h"
#include "CryptEnumerator.h"
#include <windows.h>

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

using namespace std;

CCryptEnumerator::CCryptEnumerator(void)
{
}


CCryptEnumerator::~CCryptEnumerator(void)
{
}

void CCryptEnumerator::PrintAlgorithm(unsigned long dwAlgOperations, const string & message)
{
	ULONG pAlgCount = 0;
	BCRYPT_ALGORITHM_IDENTIFIER *ppAlgList = NULL;
	ULONG dwFlags = 0;
	NTSTATUS res = STATUS_UNSUCCESSFUL;

	res= BCryptEnumAlgorithms(dwAlgOperations, &pAlgCount, &ppAlgList, dwFlags);
  
	for (ULONG i=0; i < pAlgCount; i++)
	{
		printf("%s %d: %ws\n", message.c_str(), i, ppAlgList[i].pszName);
	}
	BCryptFreeBuffer(ppAlgList);
}


void CCryptEnumerator::PrintProvider(wstring && pszAlgId, const string & message)
{
	ULONG pImplCount = 0;
	BCRYPT_PROVIDER_NAME *ppImplList = NULL;
	ULONG dwFlags = 0;
	NTSTATUS res = STATUS_UNSUCCESSFUL;

	res = BCryptEnumProviders(pszAlgId.c_str(), &pImplCount, &ppImplList, dwFlags);

	for (ULONG i=0; i < pImplCount; i++)
	{
		printf("%s %d: %ws\n", message.c_str(), i, ppImplList[i].pszProviderName);
	}

	BCryptFreeBuffer(ppImplList);
}


