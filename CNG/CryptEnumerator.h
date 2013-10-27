#pragma once
#include "CNGApi.h"
#include <string>

class CNG_EXPORTS_API CCryptEnumerator
{
public:
	CCryptEnumerator(void);
	~CCryptEnumerator(void);
public:
	void PrintAlgorithm(unsigned long dwAlgOperations, const std::string & message);
	void PrintProvider(std::wstring && pszAlgId, const std::string & message);
};

