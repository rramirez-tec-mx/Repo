#pragma once
#include <windows.h>
#include "CNGApi.h"

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

class DLL_EXPORT CCryptEnumerator
{
public:
	CCryptEnumerator(void);
	~CCryptEnumerator(void);
public:
	void PrintAlgorithm(ULONG dwAlgOperations, char * message);
	void PrintProvider(LPCWSTR pszAlgId, char * message);
};

