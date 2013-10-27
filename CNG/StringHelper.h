#pragma once
#include <string>
#include "CNGApi.h"


class CNG_EXPORTS_API StringHelper
{
public:
	StringHelper(void);
	~StringHelper(void);
public:
	std::wstring ConvertByteArrayToString(const PUCHAR & byteArray, const int arrayLength);
};

