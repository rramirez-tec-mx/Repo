#pragma once
#include "CNGApi.h"
#include <string>
#include <vector>
#include <windows.h>

class CNG_EXPORTS_API SSL
{
public:
	SSL(void);
	~SSL(void);

	void EnumCipherSuite(std::vector<std::wstring> & sslInfoCipherSuite, std::vector<std::wstring> & sslInfoCipher);
	void EnumProtocolProviders(DWORD & pdwProviderCount, NCryptProviderName **ppProviderList);
};

