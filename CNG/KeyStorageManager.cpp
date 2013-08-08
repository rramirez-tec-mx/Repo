#include "stdafx.h"
#include "KeyStorageManager.h"

using namespace std;

CKeyStorageManager::CKeyStorageManager(void)
{
}


CKeyStorageManager::~CKeyStorageManager(void)
{
}

void CKeyStorageManager::EnumStorageProvider(vector<wstring> & listOfProvider)
{
	SECURITY_STATUS ret;
	DWORD pdwProviderCount;
	NCryptProviderName *ppProviderList;
	DWORD dwFlags = 0;
	
	ret = NCryptEnumStorageProviders(&pdwProviderCount, &ppProviderList, dwFlags);
	
	if(ret != TRUE)
	{
		for (DWORD i=0; i<pdwProviderCount; i++)
		{
			listOfProvider.push_back((ppProviderList[i]).pszName);
		}
	}
	
	NCryptFreeBuffer(ppProviderList);		
}

NCRYPT_PROV_HANDLE CKeyStorageManager::OpenStorageProvider(wstring providerName)
{
	SECURITY_STATUS ret;
	DWORD dwFlags = 0;
	NCRYPT_PROV_HANDLE hProvider;
	ret = NCryptOpenStorageProvider(&hProvider, providerName.c_str(), dwFlags);
	return hProvider;
}