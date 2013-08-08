#pragma once
#include "CNGApi.h"

class DLL_EXPORT CCryptEnumerator
{
public:
	CCryptEnumerator(void);
	~CCryptEnumerator(void);
public:
	void PrintAlgorithm(unsigned long dwAlgOperations, char * message);
	void PrintProvider(std::wstring & pszAlgId, char * message);
};

