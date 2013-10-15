#pragma once
#include "CNGApi.h"
#include <string>

class DLL_EXPORT SSL
{
public:
	SSL(void);
	~SSL(void);

	void EnumCipherSuite(std::vector<std::wstring> & sslInfoCipherSuite, std::vector<std::wstring> & sslInfoCipher);
};

