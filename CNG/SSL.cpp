#include "stdafx.h"
#include "SSL.h"
#include <windows.h>
#include <bcrypt.h>
#include <Sslprovider.h>
#include "..\Log\LogOutputDebugString.h"
using namespace std;

SSL::SSL(void)
{
}


SSL::~SSL(void)
{
}

void SSL::EnumCipherSuite(vector<wstring> & sslInfoCipherSuite, vector<wstring> & sslInfoCipher)
{
	NCRYPT_PROV_HANDLE hSslProvider = NULL;  
	NCRYPT_SSL_CIPHER_SUITE *ppCipherSuite = NULL;
	PVOID ppEnumState = NULL;
    DWORD dwFlags =0;

	LPCWSTR pszProviderName = NULL;

	SECURITY_STATUS ret;

	ret = SslOpenProvider(&hSslProvider, pszProviderName, dwFlags);

	if(ret != FALSE)
	{
		LogOutputDebugString::LogMessage("SSL::SslOpenProvider failed ", GetLastError(), ret);
	}

	ret = SslEnumCipherSuites(hSslProvider, NULL, &ppCipherSuite, &ppEnumState ,dwFlags);

	if (ret != FALSE)
	{
		LogOutputDebugString::LogMessage("SSL::SslEnumCipherSuites failed ", GetLastError(), ret);
	}

	while (ret != NTE_NO_MORE_ITEMS)
	{
		ret = SslEnumCipherSuites(hSslProvider, NULL, &ppCipherSuite, &ppEnumState ,dwFlags);

		sslInfoCipherSuite.push_back(ppCipherSuite->szCipherSuite);
		sslInfoCipher.push_back(ppCipherSuite->szCipher);
		
	}

	SslFreeObject(hSslProvider, dwFlags);
}

void SSL::EnumProtocolProviders(DWORD & pdwProviderCount, NCryptProviderName **ppProviderList)
{			
	DWORD dwFlags = 0;
	
	SECURITY_STATUS ret;
	
	ret = SslEnumProtocolProviders(&pdwProviderCount, ppProviderList, dwFlags);

	if (ret != FALSE)
	{
		LogOutputDebugString::LogMessage("SSL::EnumProtocolProviders failed ", GetLastError(), ret);
	}
}

