#include "StdAfx.h"
#include "CryptEnumerator.h"


CCryptEnumerator::CCryptEnumerator(void)
{
}


CCryptEnumerator::~CCryptEnumerator(void)
{
}

void CCryptEnumerator::PrintAlgorithm(ULONG dwAlgOperations, char * message)
{
	ULONG pAlgCount=0;
	BCRYPT_ALGORITHM_IDENTIFIER *ppAlgList=NULL;
	ULONG dwFlags=0;
	NTSTATUS res =STATUS_UNSUCCESSFUL;

	res= BCryptEnumAlgorithms(dwAlgOperations, &pAlgCount, &ppAlgList, dwFlags);
  
	for (int i=0; i< (int)pAlgCount; i++)
	{
		printf("%s %d: %ws\n",message,i, ppAlgList[i].pszName);
	}
	BCryptFreeBuffer(ppAlgList);
}


void CCryptEnumerator::PrintProvider(LPCWSTR pszAlgId, char * message)
{
	ULONG pImplCount=0;
	BCRYPT_PROVIDER_NAME *ppImplList = NULL;
	ULONG dwFlags=0;
	NTSTATUS res =STATUS_UNSUCCESSFUL;

	res = BCryptEnumProviders(pszAlgId, &pImplCount, &ppImplList, dwFlags);

	for (int i=0; i< (int)pImplCount; i++)
	{
		printf("%s %d: %ws\n",message,i, ppImplList[i].pszProviderName);
	}

	BCryptFreeBuffer(ppImplList);
}


