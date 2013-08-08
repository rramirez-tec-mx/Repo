#pragma once
#include <string>
#include "CNGApi.h"


class DLL_EXPORT StringHelper
{
public:
	StringHelper(void);
	~StringHelper(void);
public:
	std::wstring ConvertByteArrayToString(PUCHAR byteArray, const int arrayLength);
};

