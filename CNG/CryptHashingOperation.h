#pragma once
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
	std::vector<unsigned char> CalcRawHash(std::wstring messageToHash, std::wstring hashAlgType, int digestLength);

private:
	std::vector<unsigned char> ConvertWStringToArrayOfByte(std::wstring stringToConvert);
	std::vector<unsigned char> CreateHash(std::wstring messageToHash, std::wstring hashAlgType);

};

