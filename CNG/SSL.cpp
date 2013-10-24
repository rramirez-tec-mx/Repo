#include "stdafx.h"
#include "SSL.h"
#include <windows.h>
#include <bcrypt.h>
#include <Sslprovider.h>

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
		char  msgbuf[200];
		sprintf_s(msgbuf, "SSL::SslOpenProvider failed. Error: %ld\n", GetLastError());
		OutputDebugStringA(msgbuf);
	}


	
	ret = SslEnumCipherSuites(hSslProvider, NULL, &ppCipherSuite, &ppEnumState ,dwFlags);

	while (ret != NTE_NO_MORE_ITEMS)
	{
		ret = SslEnumCipherSuites(hSslProvider, NULL, &ppCipherSuite, &ppEnumState ,dwFlags);

		sslInfoCipherSuite.push_back(ppCipherSuite->szCipherSuite);
		sslInfoCipher.push_back(ppCipherSuite->szCipher);
		
	}

	if(ret != FALSE)
	{
		char  msgbuf[200];
		sprintf_s(msgbuf, "SSL::SslEnumCipherSuites failed. Error: %ld\n", GetLastError());
		OutputDebugStringA(msgbuf);
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
		char  msgbuf[200];
		sprintf_s(msgbuf, "SSL::SslEnumCipherSuites failed. Error: %ld\n", GetLastError());
		OutputDebugStringA(msgbuf);
	}

	
}

