#pragma once
#include <Windows.h>
#include <string>

#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT StringHelper
{
public:
	StringHelper(void);
	~StringHelper(void);
public:
	std::wstring ConvertByteArrayToString(PUCHAR byteArray, const int arrayLength);
};

