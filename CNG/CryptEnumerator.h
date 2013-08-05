#pragma once
#include <windows.h>
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CCryptEnumerator
{
public:
	CCryptEnumerator(void);
	~CCryptEnumerator(void);
public:
	void PrintAlgorithm(ULONG dwAlgOperations, char * message);
	void PrintProvider(LPCWSTR pszAlgId, char * message);
};

