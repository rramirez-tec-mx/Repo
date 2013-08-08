#pragma once
#include <windows.h>
#include <string>
#include <memory>
#include "CNGApi.h"

class DLL_EXPORT CCryptHashingOperation
{
public:
	CCryptHashingOperation(void);
	~CCryptHashingOperation(void);

public:	
	std::wstring CalcHashInHexForm(std::wstring messageToHash, std::wstring hashAlgType, int digestLength);
	std::vector<BYTE> CalcRawHash(std::wstring messageToHash, std::wstring hashAlgType, int digestLength);

private:
	std::vector<BYTE> ConvertWStringToArrayOfByte(std::wstring stringToConvert);
	std::vector<BYTE> CreateHash(std::wstring messageToHash, std::wstring hashAlgType);

};

